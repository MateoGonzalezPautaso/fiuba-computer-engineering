#!/usr/bin/env bash
reset

echo " "
echo "**Compilando"

make unit_tester
if [ $? -ne 0 ]; then
  echo "  **Error de compilacion"
  exit 1
fi

./unit_tester
if [ $? -ne 0 ]; then
  echo "  **Uno o más tests fallaron"
  exit 1
fi

echo "**Todos los tests unitarios pasan"
echo " "

echo " "
echo "**Corriendo Valgrind"

command -v valgrind > /dev/null
if [ $? -ne 0 ]; then
  echo "ERROR: No se encuentra valgrind."
  exit 1
fi

valgrind --show-reachable=yes --leak-check=full --error-exitcode=1 ./unit_tester > /dev/null
if [ $? -ne 0 ]; then
  echo "  **Error de memoria"
  exit 1
fi


echo "**Prueba de memoria de test unitarios OK"
echo " "

