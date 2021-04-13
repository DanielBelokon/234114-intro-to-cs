#!/bin/bash

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
	range=4;
fi

if [ -z ${question} ]; then
	question=1;
fi

if [ -z ${hw} ]; then
	hw=1;
fi

for i in $(seq 1 $range)
	do ./hw${hw}q${question}.exe < Tests/hw${hw}q${question}in$i.txt | diff Tests/hw${hw}q${question}out$i.txt - 
done



