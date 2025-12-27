#!/usr/bin/env bash
reset

command -v valgrind > /dev/null
if [ $? -ne 0 ]; then
  echo "ERROR: No se encuentra valgrind."
  exit 1
fi

make game
if [ $? -ne 0 ]; then
  echo "ERROR: Error de compilacion."
  exit 1
fi

valgrind --show-reachable=yes --leak-check=full --error-exitcode=1 ./game 0
if [ $? -ne 0 ]; then
  echo "  **Error de memoria"
  exit 1
fi

echo " "
echo "**Corriendo diferencias entre Listas y Arreglos"

DIFFER="diff -d"
ERRORDIFF=0

$DIFFER gameResultArray.txt gameResultList.txt > /tmp/diff
if [ $? -ne 0 ]; then
  echo "  **Discrepancia entre Listas y Arreglos"
  ERRORDIFF=1
fi

