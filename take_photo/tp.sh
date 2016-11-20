#!/bin/bash
rm -rf *.png 
for i in `seq 1 1000`
do 
 ./takephoto  2>/dev/null
done 

