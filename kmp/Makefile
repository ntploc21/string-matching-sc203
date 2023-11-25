
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
INCLUDES = -I/path/to/headers

SRCS = kmp.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = kmp

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

kmp.o: kmp.cpp kmp.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c kmp.cpp -o kmp.o

main.o: main.cpp kmp.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o main.o

clean:
	rm -f $(OBJS) $(EXECUTABLE)