#!/bin/sh

n=0
#函数可以通过命令行传参
function()#定位
{
    for a in `ls *.c`
    do
        if [ ${#a} -eq 0 ]
        then
            echo "未找到.c文件....." 
            return 0
        fi

        n=$((n+1))
        echo "已找到$n 个文件:$a"

    done

    echo "共找到$n 个文件"
    return $n
}




function 
echo $?