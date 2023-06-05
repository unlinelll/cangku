#!/bin/sh

echo "===================="
echo "1.批量创建文件"
echo "2.批量删除文件"
echo "===================="

num=0
read -p "请输入想要执行的功能" num
if [ num -nq 1 ]||[ num -nq 2]
then 
    echo "输入的格式有误"
    exit
fi