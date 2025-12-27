#!/bin/bash
until [[ $numero -ge 5 && $numero -le 10 ]]
do
	numero=$((RANDOM % 20 + 1))
	echo "El numero es: $numero"
done
echo "Se termino el loop por el N° $numero"
