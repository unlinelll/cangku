#!/bin/bash

n=1
terminator=0
x=n
# a=false

while true
do
    read -p "请输入终止符：" terminator
    if [ $terminator = $x ] #这里sh会报错，但是bash 不会,sh只能用单个=号
    then
        echo "终止循环..."
        break
    fi
    n=$((n+1))
    echo "循环了第 $n 次"
done