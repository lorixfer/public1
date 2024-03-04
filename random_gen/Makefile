CC = g++
CFLAGS = -Wall -O3 --std=c++11

main2 : main2.o random.o
	$(CC) $? -o $@
main2.o : main2.cpp
	$(CC) -c main2.cpp -o main2.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o main2.exe seed.out

.PHONY: clean
