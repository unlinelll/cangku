#!/bin/sh

num=$1
if [ ${#num} -eq 0 ]
then
    echo "请输入要创建的函数个数:"
    read num
    echo $num
fi
echo $num
file=101

while [ $num -ge 0 ]
do
    touch $file.c
    # echo "已创建$file.c文件"
    echo $file.c
    file=$((file+1))
    num=$((num-1))
done