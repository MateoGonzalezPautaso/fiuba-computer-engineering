#!/usr/bin/env bash
reset

echo " "
echo "**Compilando"

make intensive_tester
if [ $? -ne 0 ]; then
  echo "  **Error de compilacion"
  exit 1
fi

DIFFER="diff -d"
ERRORDIFF=0

./intensive_tester int -o salida.propios.int.txt

$DIFFER salida.propios.int.txt salida.catedra.int.txt > /tmp/diff1
if [ $? -ne 0 ]; then
  echo "  **Discrepancia en el caso int"
  cat /tmp/diff1
  ERRORDIFF=1
fi

./intensive_tester string -o salida.propios.string.txt

$DIFFER salida.propios.string.txt salida.catedra.string.txt > /tmp/diff2
if [ $? -ne 0 ]; then
  echo "  **Discrepancia en el caso string"
  cat /tmp/diff2
  ERRORDIFF=1
fi

./intensive_tester array -o salida.propios.array.txt

$DIFFER salida.propios.array.txt salida.catedra.array.txt > /tmp/diff2
if [ $? -ne 0 ]; then
  echo "  **Discrepancia en el caso array"
  cat /tmp/diff2
  ERRORDIFF=1
fi

./intensive_tester list -o salida.propios.list.txt

$DIFFER salida.propios.list.txt salida.catedra.list.txt > /tmp/diff2
if [ $? -ne 0 ]; then
  echo "  **Discrepancia en el caso list"
  cat /tmp/diff2
  ERRORDIFF=1
fi

./intensive_tester card -o salida.propios.card.txt

$DIFFER salida.propios.card.txt salida.catedra.card.txt > /tmp/diff2
if [ $? -ne 0 ]; then
  echo "  **Discrepancia en el caso card"
  cat /tmp/diff2
  ERRORDIFF=1
fi

./intensive_tester game -o salida.propios.game.txt

$DIFFER salida.propios.game.txt salida.catedra.game.txt > /tmp/diff2
if [ $? -ne 0 ]; then
  echo "  **Discrepancia en el caso game"
  cat /tmp/diff2
  ERRORDIFF=1
fi


echo " "
if [ $ERRORDIFF -eq 0 ]; then
  echo "**Todos los tests intensivos pasan"
else
  exit 1
fi


echo " "
echo "**Corriendo Valgrind"

command -v valgrind > /dev/null
if [ $? -ne 0 ]; then
  echo "ERROR: No se encuentra valgrind."
  exit 1
fi

valgrind --show-reachable=yes --leak-check=full --error-exitcode=1 ./intensive_tester int string array list card game -o /dev/null
if [ $? -ne 0 ]; then
  echo "  **Error de memoria"
  exit 1
fi

echo " "
echo "**Prueba de memoria de test intensivos OK"



