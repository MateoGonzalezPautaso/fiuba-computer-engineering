#!/usr/bin/env bash
reset

make cachesim
if [ $? -ne 0 ]; then
  echo "  **Error de compilacion"
  exit 1
fi

valgrind --show-reachable=yes --leak-check=full --log-fd=9 --error-exitcode=1 ./cachesim ./trazas/adpcm.xex 2048 2 64 -v 0 15000 9>&1 1>/dev/null 2>/dev/null
if [ $? -ne 0 ]; then
  echo "  **Error de memoria"
  exit 1
fi

echo " "

