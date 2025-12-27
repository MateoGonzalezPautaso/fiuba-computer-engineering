#!/bin/bash

echo -n 'Ingrese una extension: '
read extension

archivos=$(ls | grep ".$extension")

if [[ -n $archivos ]];then
    echo "Se encontraron archivos"
    echo "$archivos"
else
    echo "No se encontraron archivos"
fi
