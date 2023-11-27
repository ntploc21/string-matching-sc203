
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
INCLUDES = -I/path/to/headers

SRCS = rabin_karp.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = rabin_karp

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

rabin_karp.o: rabin_karp.cpp rabin_karp.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c rabin_karp.cpp -o rabin_karp.o

main.o: main.cpp rabin_karp.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o main.o

clean:
	rm -f $(OBJS) $(EXECUTABLE)
