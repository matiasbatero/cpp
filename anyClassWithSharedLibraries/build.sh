#!/bin/sh

# Linux Only Build Script
# Requires: clang++ / g++
# 
# Matías Gastón Santiago

clear

if [ ! -z "$1" ]
then 
	projectName=$1;
else
	echo "You must specify project name" && exit 1
fi

echo "building $projectName ... \n"

sucess()
{
	echo "$projectName was built sucessfully"
	ls ./bin -lh | awk '{ print $9 " " $5 }'
	echo "------" && ls ./bin -lh | grep "total"
	
	return 0
}

failure()
{
	echo "cannot build project" && return 1
}

build()
{
	( clang++ -std=c++11 -Wall -w -Werror -c "./$1" -o "/tmp/$1.o" &&
	  clang++ -std=c++11 -Wall -w -Werror -o "./bin/$2" "/tmp/$1.o" -ldl ) &&
	  return 0 || return 1
}

buildSharedObject()
{
	( clang++ -std=c++11 -Wall -w -c "./$1" -o "/tmp/$1.o" && 
	  clang++ -std=c++11 -Wall -w -shared -fPIC -o "./bin/$2" "./$1" -ldl ) &&
	  return 0 || return 1
}


#Add build lines like -> build(source, binary) &&
( 
	build "main.cpp" "app" &&
	buildSharedObject "so.cpp" "someSharedObject" 
	
) && sucess || failure 


