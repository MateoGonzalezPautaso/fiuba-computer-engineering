#!/usr/bin/env bash
reset

echo " "
echo "**Compilando"

make cachesim
if [ $? -ne 0 ]; then
  echo "  **Error de compilacion"
  exit 1
fi


echo "**Corriendo tests"

pytest --testdox tests/test_args.py
pytest --testdox tests/test_ADPCM.py
pytest --testdox tests/test_FFT.py
pytest --testdox tests/test_blowfish.py

if [ $? -eq 0 ]; then
  echo "**Todos los tests pasan"
else
  exit 1
fi

echo " "

