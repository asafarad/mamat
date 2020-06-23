#!/bin/bash

## input legal check
if [[ ! -d "$1" ]]; then
	exit 1
fi

currDir=`pwd`
cd "$1" ##change directory to parameter dir
## c++ compiler
echo "CXX=g++" > "${currDir}"/objects.mk
## c++ flags for compiler
echo "CXXFLAGS=-std=c++11 -g -Wall" >> "${currDir}"/objects.mk
## libs for compiler
echo -e "LIBS=\n\n" >> "${currDir}"/objects.mk

c=`ls -1` ## list of all files in dir
for file in "${c}"; do
	filename="${file}" ## keep file name
	## find cpp files
	a=`echo "${filename}" | grep -E '\.cpp$'`
	if [[ ! a ]]; then
		## if not cpp file, skip it
		continue
	fi
	## get dependencies list of cpp file
	b=`g++ -MM ${a}`
	## print the output to the make file
	echo -e "${b}\n\n" >> "${currDir}"/objects.mk
done
## change to the original directory
cd "${currDir}"