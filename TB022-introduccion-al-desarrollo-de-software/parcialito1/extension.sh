#!/bin/bash

echo "Ingrese una extension: "
read extension

archivo=$(ls | grep ".$extension")

if [[ -n $archivo ]];then
	echo "Se encontraron archivos"
	echo "$archivo"
else
	echo "No se encontraron archivos"
fi
