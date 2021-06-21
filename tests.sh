#!/bin/bash


:' INSTRUCTIONS -
	Run in bash, follow the instructions 
	OR
	enter -w -q -r flags through commandline
	
	Default (and only, because lazy) accepted dir structure

	Store binarys in: 	./HW#/bin/
	Store tests in: 	./HW#/tests

		test input name: 	hw#q#in#.txt
		test output name:	hw#q#out#.txt
	
	# <=> Homework/Question/Test number (in & out # must match)

	Example: 

	./tests.sh
		/HW#
			/bin
				hw2q1.exe
			/tests
				hw2q1in1.txt
				hw2q1out1.txt

'

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


if [ -z ${hw} ]; then
	echo HW number:
	read hw
fi

if [ -z ${question} ]; then
	echo Question number:
	read question
fi

if [ -z ${range} ]; then
	echo Test amount:
	read range
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



