
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
INCLUDES = -I/path/to/headers

SRCS = aho_corasick.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = aho_corasick

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

aho_corasick.o: aho_corasick.cpp aho_corasick.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c aho_corasick.cpp -o aho_corasick.o

main.o: main.cpp aho_corasick.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o main.o

clean:
	rm -f $(OBJS) $(EXECUTABLE)
