#!/bin/sh

#用于接收输入的路径
DIR=0

#录入路径文件夹
read -p "请输入需要搜索的路径" DIR
echo "输入的路径文件夹是$DIR"

#录入行首数据
S=a
# read -p "请输入行首数据" S
# echo "输入行首数据为$S"

#录入行尾数据
E=d
# read -p "请输入行尾数据" E
# echo "输入的行尾数据为$E"

#搜索匹配行首为app,行尾是end的数据
grep "e\{3,\}" $DIR/* --color -n
