#!/usr/bin/awk -f


BEGIN{
    FS="[ :\t]"
    print "filename:",FILENAME
}

{
if ($2==167){
    print "第"NR"行匹配数据";
    print $0
}
}
#这里是利用awk数组来存储对应键的出现次数，对每行进行一个遍历，到最后在进行遍历输出，注意这里的count是一个键的列表，而想得到键出现的次数则是需要用count[word]对应的键进行引用输出
awk -F"[ :\t]" '{print ""NR":",$0}{for(i=0;i<=NR;i++){if($i!="[ \t\n]"&& $i!=$0){count[$i]++}}}END{for(word in count){print "键:"word ,"出现次数:"count[word]}}' 1.txt
#上面还使用了一个过滤器来过滤掉整行的键，如果不过滤则会将整行都作为一个键来存储数据