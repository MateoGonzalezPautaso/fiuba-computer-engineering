#!/bin/bash

echo "Ingrese el nombre de un archivo: "
read nombre

echo "1) Para ver el contenido del archivo"
echo "2) Para editar el archivo"
echo "3) Para ver los permisos del archivo"
echo "*) Para salir"

read ingreso
case $ingreso in
1)
	cat $nombre
	;;
2)
	nano $nombre
	;;
3)
	ls -l $nombre
	;;
*)
	echo "exit"
	;;
esac

