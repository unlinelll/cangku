#!/bin/sh

n=1

# for a in `ls *.c`
# do
#     echo "第$n 个文件:$a \n"
#     cat $a -n
#     echo "\n"
#     n=$((n+1))
#     echo "($a)文件中的单词个数为"
#     wc -w $a 

# done

wc `ls *.c`|awk '{print $1}{print $4}'
