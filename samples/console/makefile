#makefile
# Created on: 2014/09/06
#     Author: junya
    
TARGET = test

CXXFLAGS = -Wall -I ../../include -O3 -g3 -ggdb 
CC = g++

$(TARGET):    $(TARGET).o
	$(CC)  -o $(TARGET) $(TARGET).o ../../src/web/web.a ../../src/validator/validator.a ../../src/db/db.a ../../src/core/core.a -ldl -lmysqlclient
   
$(TARGET).o:    $(TARGET).cpp
	$(CC) $(CXXFLAGS) -c $(TARGET).cpp

all:    $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).o
