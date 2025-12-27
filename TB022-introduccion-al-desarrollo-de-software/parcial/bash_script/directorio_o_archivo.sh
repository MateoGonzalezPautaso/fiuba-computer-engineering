#!/bin/bash

echo -n "Ingrese un parametro: "
read parametro

if [[ -d $parametro ]];then
    echo "Es un directorio"
    ls $parametro
elif [[ -f $parametro ]];then
    echo "Es un archivo"
    cat $parametro
else
    echo "No es un archivo ni un parametro"
fi
