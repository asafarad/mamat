#!/bin/bash

if [[ ! -d "$1" ]]; then
	exit 1
fi

currDir=`pwd`
cd "$1"

echo "CXX=g++" > objects.mk
echo "CXXFLAGS=-std=c++11 -g -Wall" >> objects.mk
echo "LIBS=" >> objects.mk
echo "RM=rm -f" >> objects.mk

c=`ls -1`
for file in "${c}"; do
	filename="$file"
	a=`echo "${filename}" | grep -E '\.cpp$'`
	if [[ ! a ]]; then
		continue
	fi
	b=`g++ -MM ${a}`
	echo -e "${b}" >> objects.mk
done

#Clean
echo "clean:" >> objects.mk
echo -e "\t$""(RM) ADT *.o *.bak *~ "#"* core'" >> objects.mk

cd "${currDir}"