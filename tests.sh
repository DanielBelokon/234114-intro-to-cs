#!/bin/bash

while true
do
while getopts w:q:n:r: flag
do
	case "${flag}" in
		w) hw=${OPTARG};;
		q) question=${OPTARG};;
		n) num=${OPTARG};;
		r) range=${OPTARG};;
	esac
done

if [ -z ${range} ]; then
	echo Test amount:
	read range
fi

if [ -z ${question} ]; then
	echo Question number:
	read question
fi

if [ -z ${hw} ]; then
	echo HW number:
	read hw
fi

for i in $(seq 1 $range)
	do echo "------------------------------->";echo "Doing HW${hw}Q${question} - test $i"; HW${hw}/bin/hw${hw}q${question}.exe < HW${hw}/tests/hw${hw}q${question}in$i.txt | diff --strip-trailing-cr HW${hw}/tests/hw${hw}q${question}out$i.txt - 
done

unset range
unset num
unset question
unset hw
echo done
done



