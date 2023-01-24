C=g++
CFLAGS=-I.

build: main_6502.o 
  $(CC) -o output main_6502.o