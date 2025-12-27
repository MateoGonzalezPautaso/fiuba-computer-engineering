/* See COPYRIGHT for copyright information. */

#ifndef JOS_KERN_SCHED_H
#define JOS_KERN_SCHED_H
#ifndef JOS_KERNEL
#error "This is a JOS kernel header; user programs should not #include it"
#endif

#define MAX_HISTORY 155

// This function does not return.
void sched_yield(void) __attribute__((noreturn));

typedef struct sched_stats {
	envid_t history[MAX_HISTORY];
	uint32_t history_size;

	uint32_t sched_calls;
	uint32_t halt_count;

	uint32_t total_priority_boost_count;
	uint32_t total_priority_drop_count;
} sched_stats_t;

#endif  // !JOS_KERN_SCHED_H
