JMP seguir

seguir:
SET R0, 0xFF
SET R1, 0x01

ADD R0, R1
JRC R0; bucle infinito
