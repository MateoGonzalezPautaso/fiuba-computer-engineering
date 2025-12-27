#include <inc/assert.h>
#include <inc/x86.h>
#include <kern/spinlock.h>
#include <kern/env.h>
#include <kern/pmap.h>
#include <kern/monitor.h>
#include <kern/syscall.h>
#include <kern/sched.h>

#define MAX_RUNS_BEFORE_DROP 5
#define MAX_CALLS_BEFORE_BOOST 10

sched_stats_t stats = { 0 };


void sched_halt(void);

// Scheduler con prioridades

void
boost_priorities()
{
	for (int i = 0; i < NENV; i++) {
		struct Env *env_actual = &envs[i];

		env_actual->env_priority = HIGHEST_PRIORITY;
		env_actual->priority_boost_count++;
		env_actual->env_priority_runs = 0;
	}
	stats.total_priority_boost_count++;
}

void
drop_priority(struct Env *env)
{
	uint32_t dropped_priority = env->env_priority + 1;
	env->env_priority = MIN(dropped_priority, LOWEST_PRIORITY);
	env->env_priority_runs = 0;
	env->priority_drop_count++;

	stats.total_priority_drop_count++;
}


struct Env *
siguiente_a_ejecutar_prioridades(void)
{
	struct Env *mejor_env = NULL;
	int mejor_prioridad = LOWEST_PRIORITY + 1;

	int comienzo = curenv ? (ENVX(curenv->env_id) + 1) % NENV : 0;

	for (int i = 0; i < NENV; i++) {
		int indice_actual = (comienzo + i) % NENV;
		struct Env *env_actual = &envs[indice_actual];

		if (env_actual->env_status == ENV_RUNNABLE) {
			if (env_actual->env_priority < mejor_prioridad) {
				mejor_prioridad = env_actual->env_priority;
				mejor_env = env_actual;
			} else if (env_actual->env_priority == mejor_prioridad &&
			           !mejor_env) {
				mejor_env = env_actual;
			}
		}
	}

	return mejor_env;
}


// Scheduler sin prioridades

struct Env *
siguiente_a_ejecutar_RR(int comienzo_round)
{
	for (int i = 0; i <= NENV; i++) {
		int indice_actual = (comienzo_round + i) % NENV;
		struct Env *env_actual = &envs[indice_actual];

		if (env_actual->env_status == ENV_RUNNABLE) {
			return env_actual;
		}
	}

	return NULL;
}

// Choose a user environment to run and run it.
void
sched_yield(void)
{
	struct Env *env_a_ejecutar = NULL;
	stats.sched_calls++;

#ifdef SCHED_ROUND_ROBIN
	// Implement simple round-robin scheduling.
	//
	// Search through 'envs' for an ENV_RUNNABLE environment in
	// circular fashion starting just after the env this CPU was
	// last running. Switch to the first such environment found.
	//
	// If no envs are runnable, but the environment previously
	// running on this CPU is still ENV_RUNNING, it's okay to
	// choose that environment.
	//
	// Never choose an environment that's currently running on
	// another CPU (env_status == ENV_RUNNING). If there are
	// no runnable environments, simply drop through to the code
	// below to halt the cpu.

	int comienzo_round;
	if (curenv) {
		comienzo_round =
		        ENVX(curenv->env_id) +
		        1;  // La ronda empieza desde el proceso siguiente al curenv
	} else {
		comienzo_round = 0;
	}

	env_a_ejecutar = siguiente_a_ejecutar_RR(comienzo_round);

#endif

#ifdef SCHED_PRIORITIES
	// Implement simple priorities scheduling.
	//
	// Environments now have a "priority" so it must be consider
	// when the selection is performed.
	//
	// Be careful to not fall in "starvation" such that only one
	// environment is selected and run every time.

	if (stats.sched_calls % MAX_CALLS_BEFORE_BOOST == 0) {
		boost_priorities();
	}

	env_a_ejecutar = siguiente_a_ejecutar_prioridades();

#endif


	// Si no hay otro proceso runnable, y el actual sigue corriendo, lo dejamos
	if (!env_a_ejecutar && curenv && curenv->env_status == ENV_RUNNING)
		env_a_ejecutar = curenv;

	if (env_a_ejecutar) {
		env_a_ejecutar->env_priority_runs += 1;

#ifdef SCHED_PRIORITIES
		if (env_a_ejecutar->env_priority_runs >= MAX_RUNS_BEFORE_DROP) {
			drop_priority(env_a_ejecutar);
		}
#endif

		stats.history[stats.history_size % MAX_HISTORY] =
		        env_a_ejecutar->env_id;
		stats.history_size++;
		env_run(env_a_ejecutar);
	}

	stats.halt_count++;
	// sched_halt never returns
	sched_halt();
	panic("sched_yield should never return");
}


void
imprimir_estadisticas()
{
	cprintf("\nStats Sched\n");

	cprintf("Scheduler calls: %d\n", stats.sched_calls);
	cprintf("Times the processor halted: %d\n", stats.halt_count);
	cprintf("Total priority boosts: %d\n", stats.total_priority_boost_count);
	cprintf("Total priority drops by scheduler: %d\n",
	        stats.total_priority_drop_count);
	cprintf("Total processes scheduled: %d\n", stats.history_size);

	cprintf("\nScheduler's history of the last %d executed and selected "
	        "processes\n",
	        stats.history_size);
	int cantidad_procesos = (MAX_HISTORY < stats.history_size)
	                                ? MAX_HISTORY
	                                : stats.history_size;
	for (int i = 0; i < cantidad_procesos; i++) {
		cprintf("ENVID: %d\n", stats.history[i]);
	}
}


// Halt this CPU when there is nothing to do. Wait until the
// timer interrupt wakes it up. This function never returns.
//
void
sched_halt(void)
{
	int i;

	// For debugging and testing purposes, if there are no runnable
	// environments in the system, then drop into the kernel monitor.
	for (i = 0; i < NENV; i++) {
		if ((envs[i].env_status == ENV_RUNNABLE ||
		     envs[i].env_status == ENV_RUNNING ||
		     envs[i].env_status == ENV_DYING))
			break;
	}
	if (i == NENV) {
		cprintf("No runnable environments in the system!\n");
		imprimir_estadisticas();

		while (1)
			monitor(NULL);
	}

	// Mark that no environment is running on this CPU
	curenv = NULL;
	lcr3(PADDR(kern_pgdir));

	// Mark that this CPU is in the HALT state, so that when
	// timer interupts come in, we know we should re-acquire the
	// big kernel lock
	xchg(&thiscpu->cpu_status, CPU_HALTED);

	// Release the big kernel lock as if we were "leaving" the kernel
	unlock_kernel();

	// Once the scheduler has finishied it's work, print statistics on
	// performance. Your code here

	// Reset stack pointer, enable interrupts and then halt.
	asm volatile("movl $0, %%ebp\n"
	             "movl %0, %%esp\n"
	             "pushl $0\n"
	             "pushl $0\n"
	             "sti\n"
	             "1:\n"
	             "hlt\n"
	             "jmp 1b\n"
	             :
	             : "a"(thiscpu->cpu_ts.ts_esp0));
}