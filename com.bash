#!/usr/bin/env bash
rm ./program
gcc -Wall -o program program.c

echo "Testing data1.txt"
./program alice feet < data1.txt #> test1out.txt

#echo "Testing data2.txt"
#./program a b c < data2.txt
#echo "Testing data3.txt"
#./program a b c < data3.txt
git add .
git commit -m "run"