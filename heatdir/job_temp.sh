#!/bin/bash

# Assign the filename
filename="Makefile"
# Declare an array of string with type
declare -a StringArray=("CFLAGS = -O1" "CFLAGS = -O2" "CFLAGS = -O3" "CFLAGS = -Ofast"
                        "CFLAGS = -O2 -xhost" "CFLAGS = -O2 -xCORE-AVX512" "CFLAGS = -O2 -xCORE-AVX512 -ipo" "CFLAGS = -O2 -ipo"
                        "CFLAGS = -O2 -xCORE-AVX512 -fno-alias" "CFLAGS = -O2 -xCORE-AVX512 -fno-alias" "CFLAGS = -O2 -fno-alias"
                        "CFLAGS = -O3 -xhost" "CFLAGS = -O3 -xCORE-AVX512" "CFLAGS = -O3 -xCORE-AVX512 -ipo" "CFLAGS = -O3 -ipo"
                        "CFLAGS = -O3 -xCORE-AVX512 -fno-alias" "CFLAGS = -O3 -xCORE-AVX512 -fno-alias" "CFLAGS = -O3 -fno-alias"
                        "CFLAGS = -Ofast -xhost" "CFLAGS = -Ofast -xCORE-AVX512" "CFLAGS = -Ofast -xCORE-AVX512 -ipo" "CFLAGS = -Ofast -ipo"
                        "CFLAGS = -Ofast -xCORE-AVX512 -fno-alias" "CFLAGS = -Ofast -xCORE-AVX512 -fno-alias" "CFLAGS = -Ofast -fno-alias")
searchString="CFLAGS = -O0"

for ((i =0; i < ${#StringArray[@]}; i++)) do
# echo ${StringArray[$i]}
 echo "Cleaning files"
 make clean
 sleep 3
 sed -i "s/$searchString/${StringArray[$i]}/" $filename
 echo -e "Replacement done\n"
 sleep 3
 echo "Building new code"
 make
 sleep 10
 echo "Running the executable"
 echo -e "Compiler flags used: $val" >> log.txt
 for i in {1..2}; do 
     echo "run $i" >> log.txt 
     ./heat test.dat >> log.txt
 done
 echo -e "---------------------------------------------" >> log.txt
 searchString=$val
done
