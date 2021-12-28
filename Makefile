
output: main.o ThreadPool.o
	gcc main.o ThreadPool.o -o output

main.o: main.c
	gcc -c main.c

ThreadPool.o: ThreadPool.c ThreadPool.h
	gcc -c ThreadPool.c

clean:
	rm *.o output

