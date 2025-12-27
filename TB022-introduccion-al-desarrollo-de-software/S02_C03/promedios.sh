#!/bin/bash

for i in {1..10};do
	echo "Ingrese un valor entero: "
	read ingreso
	total=$(($total + $ingreso))

done

#promedio=$(($total/10))
#echo "El promedio es: $promedio"
promedio=$(echo "scale=2; $total / 10" | bc)
echo "El promedio es: $promedio"
