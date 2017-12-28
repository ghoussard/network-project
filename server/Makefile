all: main.o server.o common.o
	gcc main.o server.o common.o -o server
	rm *.o

main.o: src/main.c src/server.c ../common/common.c
	gcc -c src/main.c -I headers -o main.o

server.o: src/server.c
	gcc -c src/server.c -I headers -o server.o

common.o:  ../common/common.c
	gcc -c ../common/common.c -o common.o