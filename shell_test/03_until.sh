#!/bin/sh

n=0

until [ $n -gt 100 ]
do 
    echo "$n"
    n=$((n+101))
    echo "-----$n"
    n=$((n+3))
    echo "+++$n"

done