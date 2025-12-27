#include <inc/lib.h>

void
umain(int argc, char **argv)
{
	for (int i = 0; i < 20; i++) {
		cprintf("---Low priority---\n");
		cprintf("i am environment %08x | current priority %u\n",
		        thisenv->env_id,
		        sys_getpriority());

		sys_droppriority(sys_getenvid(), 1);
		cprintf("i am environment %08x | current priority after drop "
		        "%u\n",
		        thisenv->env_id,
		        sys_getpriority());

		sys_yield();
	}
}
