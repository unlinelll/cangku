a=0

a=$((a+1))

case $a in
0)
echo "输出为0";;
1)
echo "输出为1";;
*)
echo "输出??";;
esac


# if [ $# -eq 0 ];then
    
#     echo "输出为1"
#     echo "\$0=$0"
# else
#     echo "输出不为1"
#     echo "\$#=$#"
# fi
