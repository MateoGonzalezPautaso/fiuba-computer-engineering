JMP seguir

seguir:
SET R0, 0xF0 
SET R1, 0x01 
SET R2, 0x00

ADD R0, R1
JRN R2; bucle infinito
