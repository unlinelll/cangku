#!/bin/bash



grep '^yy' ./*.c --color -n
echo "============="
grep " " ./*.c ./*.txt --color -n
echo "=============="
grep 'a*d' ./*.txt --color -n
echo "=============="
grep 'a\+d' ./*.txt --color -n
echo "=============="
grep 'a\?d' ./*.txt --color -n #别忘了转义符号
echo "=============="

grep 'e\{3,5\}' ./*.txt --color -n
echo "=============="
grep 'e\{2,5\}\?' ./*.txt --color -n
#这里没法实现非贪婪匹配，可以使用其他元字符来实现
echo "=============="
grep 'e[^0-9'\t']\+' ./*.txt --color -n