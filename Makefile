CC=g++
CFLAGS=-Wall -Werror -fopenmp

INCLUDE=-I.
LIBPATH=-L.
LIBS=

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: gas

gas: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(OBJS) $(LIBPATH) $(LIBS)
	
$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	
clean:
	rm -f *.o gas