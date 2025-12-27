#!/bin/bash

for archivo in $(ls | grep *.txt)
do
	cat $archivo
done
