#!/bin/bash

File=`ls`

for a in $File
do
    if [ ! -r $a ]||[ ! -w $a ]||[ ! -x $a ]
    then
        chmod 777 $a
    fi
done