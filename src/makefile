#makefile
# Created on: 2014/09/06
#     Author: junya
    
TARGET = test

CXXFLAGS = -Wall -I ../include -O0
CC = g++

$(TARGET):    $(TARGET).o
	$(CC) -o $(TARGET) $(TARGET).o
   
$(TARGET).o:    $(TARGET).cpp
	$(CC) $(CXXFLAGS) -c -g $(TARGET).cpp

all:    $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).o
