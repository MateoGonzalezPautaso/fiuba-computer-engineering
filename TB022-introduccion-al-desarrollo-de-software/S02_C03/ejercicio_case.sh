#!/bin/bash

echo "Ingrese el nombre de un archivo: "
read archivo

echo "1- para ver el contenido del archivo $archivo"
echo "2- para editar el archivo $archivo con el editor nano"
echo "3- para ver los permisos del archivo $archivo"
echo "*- para salir"

read ingreso
case $ingreso in

1)	echo "Ver contenido del archivo $archivo"
	cat $archivo
	;;
2)	echo "Editar el archivo $archivo con nano"
	nano $archivo
	;;
3)	echo "Ver los permisos del archivo $archivo"
	ls -l $archivo
	;;
*)	echo "Salir"
	;;
esac
