#!/bin/bash

echo -n "Ingrese un tipo de extension: "
read extension

archivos=$(ls | grep ".$extension")

if [ -z $archivos ];then
	echo "No se encontraron archivos"
else
	echo "Se encontraron archivos"
	echo "$archivos"
fi
