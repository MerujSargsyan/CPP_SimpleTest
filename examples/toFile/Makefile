CC = g++
CFLAGS = -Wall -Wextra -O3 -std=c++17
DIR = ../..

all: tests

tests: simple_test

simple_test: simple_test.cpp $(DIR)/SimpleTester.hpp
	$(CC) $(CFLAGS) simple_test.cpp -o build/simple_test -I$(DIR)

run: 
	build/simple_test
