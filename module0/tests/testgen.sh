#!/bin/bash

#Generate empty file named 'a'.
touch a

#Generate simple test file
echo "a1 b  A   c2dBe    3fCD" > test.txt

#Generate long-filename whitespace test file
character=1
longString=""
while [ $character -le 255 ]
do
    longString="${longString}t"
    ((character++))
done

echo -e '\t\t\t\t\t\n          \n' > $longString
