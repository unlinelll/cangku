#!/bin/sh

if [ $# -eq 0 ]
then
    echo "无命令行参数"
else
    if [ -e $1 ] && [ -r $1 ]
    then
        cat $1
    elif [ -e $1 ] && [ ! -r $1 ] #这里注意也要加then关键字
    then
        chmod +r $1
        cat $1
    else
        touch $1
        chmod +r $1
        echo "hello" > $1
        cat $1
    fi
fi