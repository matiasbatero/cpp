#!/bin/bash


# build main (core) executable:

# make .o objects
g++ -Wall -fPIC -fexceptions -std=c++11 -c 'null.cxx' -o 'null.o'
g++ -Wall -fPIC -fexceptions -std=c++11 -c 'type.0.cxx' -o 'type.0.o'
g++ -Wall -fPIC -fexceptions -std=c++11 -c 'type.1.cxx' -o 'type.1.o'
g++ -Wall -fPIC -fexceptions -std=c++11 -c 'type.cxx' -o 'type.o'

# make (.o) as shared (.so)
g++ -shared  'null.o' -o 'null.so'
g++ -shared  'type.0.o' -o '_type.so.0'
g++ -shared  'type.1.o' -o '_type.so.1'
g++ -shared  'type.o' -o '_type.so'

g++ -shared -o 'type.so.0' '_type.so.0' 'null.so'
g++ -shared -o 'type.so.0' '_type.so.1' '_type.so.0'
g++ -shared -o 'type.so' '_type.so' '_type.so.1'


# link main core
g++ -Wall -fexceptions -std=c++11 -c  'main.cxx' -o 'main.o'
g++ -o 'main' 'main.o' 'type.so'


# clean

#rm *.o _*.so
