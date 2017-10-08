#!/bin/bash

#chmod +x code-of-bash.sh			#Bu komut yönetici izni sağlar
#Eğer betiği /usr/bin/ dizinine atarsanız uçbirime code-of-bash.sh yazıp betiği çalıştırabilirsiniz
#./code-of-bash.sh

cp a.out Example01/a.out
cp a.out Example02/a.out
cp a.out Example03/a.out
cp a.out Example04/a.out
cp a.out Example05/a.out
cp a.out Example06/a.out
cp a.out ExampleHw/a.out

cd ExampleHw
./a.out
rm a.out
cd ..
cd Example01
./a.out
rm a.out
cd ..
cd Example02
./a.out
rm a.out
cd ..
cd Example03
./a.out
rm a.out
cd ..
cd Example04
./a.out
rm a.out
cd ..
cd Example05
./a.out
rm a.out
cd ..
cd Example06
./a.out
rm a.out
cd ..

