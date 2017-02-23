#!/bin/sh
wget -w 3 -i hansard
for pdf in `ls | grep WEEKLY.pdf`
do
	echo "Extracting "$pdf
	python3 pdf2txt.py -o $pdf".txt" $pdf
done
for pdf in `ls | grep DAILY.pdf`
do
	echo "Extracting "$pdf
	python3 pdf2txt.py -o $pdf".txt" $pdf
done
