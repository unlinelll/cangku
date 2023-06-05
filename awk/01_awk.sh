#!/bin/sh

# awk -v FS="[ ?:]" 'BEGIN{x="hello"&&OFS="+"}{print NR,$1,$2,$3}' ./1.txt



awk 'BEGIN{x="6."&&FS="[: ?]"}{print $1 ,$2>$3}' 1.txt