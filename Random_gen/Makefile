CC = g++
CFLAGS = -Wall -O3 --std=c++11

main : main.o random.o
	$(CC) $? -o $@
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o main.exe seed.out

.PHONY: clean
