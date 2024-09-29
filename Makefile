#	Makefile

CC = g++
CFLAGS = -Wall -pedantic
LIBS = -larmadillo
TARGET = 
SOURCE = $(wildcard src/*.cpp)
TEXT_SRC = src/normalizer.cpp
TEST_PREFIX = test_

all:lib

text: main.cpp
	$(CC) -o main $< $(TEXT_SRC) -g $(CFLAGS)

lib: $(SOURCE)
	$(CC) -o nnet_interface.so $^ -shared -fPIC $(CFLAGS) $(LIBS)

main: main.cpp
	$(CC) -o $@ $< $(SOURCE) $(CFLAGS) $(LIBS)

$(TEST_PREFIX)%: $(TEST_PREFIX)%.cpp
	$(CC) -o $(@).out $< $(SOURCE) -g $(LIBS) $(CFLAGS)


clean:
	rm -f *.so main test_*.out
