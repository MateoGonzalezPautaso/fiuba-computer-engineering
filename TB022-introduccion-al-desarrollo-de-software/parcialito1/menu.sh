#!/bin/bash

echo "Ingrese el nombre de un archivo: "
read archivo

echo "1- Ingresar una palabra y reemplazarla por **** en $archivo"
echo "2- Abrir el archivo"
echo "3- Realizar una copia de $archivo llamada menu_copia.sh"
echo "4- Ingresar un email y validarlo mediante RE"
echo "5- Salir"

read ingreso
case $ingreso in

1)	echo "Ingresar palabra: "
	read palabra
	sed -i "s/$palabra/****/g" $archivo
	echo "Palabra/s reemplazada/s"
	;;
2)	nano $archivo
	;;
3)	cp $archivo menu_copia.sh
	echo "Copia realizada"
	;;
4)	echo "Ingrese un email:"
	read email
	if [[ "$email" =~ ^[A-Za-z]+@[A-Za-z]+.[A-Za-z]+$ ]];then
		echo "Email validado"
	else
		echo "Email invalidado"
	fi
	;;
5)	echo "Salir"
	;;
esac
