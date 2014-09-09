#makefile
# Created on: 2014/09/06
#     Author: junya
    
TARGET = Kozaiku_Template_Autogen.so

CXXFLAGS = -Wall -I ../ -O0 -g3 -ggdb
CC = g++
KOZAIKU = ./Kozaiku.pl

$(TARGET): Kozaiku_Template_Autogen_sample.o
	$(CC) -shared $^  -o $@
.cpp.o:
	$(CC) $(CXXFLAGS) -c $<

all:    $(TARGET)

gen:
	$(KOZAIKU) -d template

clean:
	rm -f $(TARGET)
	rm -f *.cpp *.o Kozaiku_Template_Autogen.h
