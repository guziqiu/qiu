#########################################################################
# File Name: 6.while.sh
# Author: 古子秋
# mail: 
# Created Time: Sun 29 Nov 2020 06:43:43 PM CST
#########################################################################
#!/bin/bash


num=0
while [[ $num -lt 100 ]];do
	echo ${num}
	num=$[ ${num} + 1 ]
done

