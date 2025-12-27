JMP seguir

seguir:
SET R0, 0x55
SET R1, 0xAA

MIX R0, R1

halt:
JMP halt
