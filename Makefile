CC     = gcc
CFLAGS = -march=native

OBJS = sorting.o random.o bubblesort.o insertionsort.o selectsort.o \
       shellsort.o heapsort.o
INCL = random.h
LIBS = -lm
EXEC = sorting

all: $(EXEC)

clean:
	rm $(OBJS) $(EXEC) *~
	
tidy:
	rm $(OBJS) *~
	
$(EXEC): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LIBS)