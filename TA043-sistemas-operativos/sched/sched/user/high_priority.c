#include <inc/lib.h>

void
umain(int argc, char **argv)
{
	for (int i = 0; i < 20; i++) {
		cprintf("---High priority---\n");
		cprintf("i am environment %08x | current priority %u\n",
		        thisenv->env_id,
		        sys_getpriority());
		sys_yield();
	}
}
