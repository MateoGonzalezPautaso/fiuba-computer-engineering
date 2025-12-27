JMP seguir

seguir:
SET R0, 0xF0
SET R1, 0x01

ADD R0, R1; C y Z prendidos
LOADf R2

halt:
JMP halt