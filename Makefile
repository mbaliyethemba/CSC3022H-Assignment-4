CC = g++
CCFLAGS=-c -std=c++11
LDFLAGS=-lm
OBJECTS= image.o driver.o
TARGET = imageops

$(TARGET):	$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

driver.o: driver.cpp
	$(CC) $(CCFLAGS) driver.cpp

image.o: image.cpp image.h
	$(CC) $(CCFLAGS) image.cpp
	
clean:
	@rm $(OBJECTS)
	@rm $(TARGET)
	
run_test: UnitTests.o 
	$(CC) UnitTests.o image.o -o UnitTests
	
UnitTests.o: UnitTests.cpp
	$(CC) $(CCFLAGS) -w  -o UnitTests.o -c UnitTests.cpp 
