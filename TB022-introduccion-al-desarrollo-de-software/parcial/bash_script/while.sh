#!/bin/bash

i=1

while [[ $i -le 5 ]];do
    echo "Bienvenido por vez numero $i"
    i=$(( $i + 1 ))
done