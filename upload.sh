#!/bin/bash
for i in  `ls *.jpg |xargs`
do 
curl --form "fileupload=@$i" http://www.yoyojacky.com/?upload
sleep 1
if [ $? -eq 0 ];then
rm -rf $i
else 
    echo "upload failue." 
fi
done
