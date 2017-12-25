all: main.o server.o utils.o
	gcc main.o server.o utils.o -o server
	rm *.o

main.o: src/main.c src/server.c ../libs/utils/utils.c
	gcc -c src/main.c -I headers -o main.o

server.o: src/server.c
	gcc -c src/server.c -I headers -o server.o

utils.o:  ../libs/utils/utils.c
	gcc -c ../libs/utils/utils.c -o utils.o