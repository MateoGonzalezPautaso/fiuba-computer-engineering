#!/bin/bash

echo -n "Ingrese una nota:"
read x

if [ $x -ge 4 ];then
	echo "Ud. aprobo el examen"
else
	echo "No aprobo el examen, su nota es menor a 4"
fi
