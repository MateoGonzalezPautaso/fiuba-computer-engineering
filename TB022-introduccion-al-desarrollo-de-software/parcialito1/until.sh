#!/bin/bash

n=1
until [[ $n -ge 5 && $n -le 10 ]];do

	n=$(( 1 + RANDOM % 20))
	echo $n
done
echo "Se termino el ciclo con: $n"
