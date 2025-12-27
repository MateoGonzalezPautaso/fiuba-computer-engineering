#!/bin/bash

echo -n "ingrese el nombre de un archivo: "
read archivo

echo "1) Para ver el contenido del archivo"
echo "2) Para editar el contenido del archivo"
echo "3) Para ver los permisos del archivo"
echo "*) Para salir"
read ingreso

case $ingreso in
1)
    cat $archivo
    ;;
2)
    nano $archivo
    ;;
3)
    ls -l $archivo
    ;;
*)
    echo "Salir"
    ;;
esac