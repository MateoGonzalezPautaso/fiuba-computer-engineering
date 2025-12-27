#!/bin/bash

echo -n "Ingrese un archivo o directorio: "
read parametro

if [ -d $parametro ];then
	ls $parametro
elif [ -f $parametro ];then
	cat $parametro
else
	echo "No es archivo ni directorio"
fi

