JMP seguir

seguir:
SET R0, 0xFF
SET R1, 0x01

ADD R0, R1; C y Z prendidos
SETf 0x04; Se fuerza C=0 Z=0 N=1

halt:
JMP halt