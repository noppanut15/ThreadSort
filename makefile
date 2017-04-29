CC = g++
CFLAGS = -std=c++11
OBJECTS = thread_sort.o
EXEC = Thread-Sort

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)
	-rm *.o

thread_sort.o: thread_sort.cpp
	$(CC) $(CFLAGS) -c thread_sort.cpp

.PHONY : clean

clean:
	-rm *.o

clear:
	-rm $(EXEC) *.o

run:
	./$(EXEC)

