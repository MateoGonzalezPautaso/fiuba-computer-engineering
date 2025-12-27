#!/bin/bash

MASTER="TallerLogica-Combinatorios-individual.circ"
TRUTH="salida_catedra.txt"
OUTPUT="output-entrega.txt"
RUN_TEST="logisim-evolution --toplevel-circuit "verificador" -tty table"

echo "RUN_TEST: ${RUN_TEST}"
echo "OUTPUT: ${OUTPUT}"

${RUN_TEST} ${MASTER} > "${OUTPUT}"

if [ ! -f "${OUTPUT}" ]; then
    echo "ERROR: No se pudo generar el archivo de salida"
    exit 1
fi

if diff -q "${OUTPUT}" "${TRUTH}"; then
    echo "OK"
    exit 0
else
    echo "ERROR: Las salidas no coinciden"
    diff -y --suppress-common-lines "${OUTPUT}" "${TRUTH}"
    exit 1
fi
``` 