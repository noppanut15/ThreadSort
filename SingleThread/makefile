CC = g++
CFLAGS = -std=c++11
OBJECTS = single_thread_sort.o
EXEC = Single-Thread-Sort

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)
	-rm *.o

single_thread_sort.o: single_thread_sort.cpp
	$(CC) $(CFLAGS) -c single_thread_sort.cpp

.PHONY : clean

clean:
	-rm *.o

clear:
	-rm $(EXEC) *.o

run:
	./$(EXEC)

