#!/bin/bash
for i in  `ls *.png |xargs`
do 
curl -sT $i www.yoyojacky.com:9001
sleep 1
if [ $? -eq 0 ];then
rm -rf $i
else 
    echo "upload failue." 
fi
done
