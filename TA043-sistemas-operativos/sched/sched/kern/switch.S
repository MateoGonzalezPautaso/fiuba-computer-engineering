/*
 * It should restore the register values in the Trapframe with the 'iret' instruction.
 * This exits the kernel and starts executing some environment's code.
 *
 * This function does not return.
*/


.globl context_switch;
context_switch:
    # la primera direccion del stack pointer es el return adress
	add $4, %esp	# esp = puntero al Trapframe
	mov (%esp), %esp

	popal	# restaura edi, esi, ebp, salta oesp, ebx, edx, ecx, eax
	# despues de popal el esp queda apuntando a tf_es

	pop %es		# restaura es y mueve el esp a los siguientes 32 bits (restaura tf_es y tf_padding1)
	pop %ds 	# mismo caso pero con ds

	add $8, %esp	# esp saltea tf_trapno y tf_err. esp = tf_eip

	iret	# se restauran atómicamente eip, cs y esp

spin:
	jmp spin
