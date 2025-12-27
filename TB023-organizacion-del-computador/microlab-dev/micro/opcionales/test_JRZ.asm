JMP seguir

seguir:
SET R0, 0xFE
SET R1, 0x02

ADD R0, R1
JRZ R0; bucle infinito
