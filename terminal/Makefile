all: main.o terminal.o common.o
	gcc main.o terminal.o common.o -o terminal
	rm *.o

main.o: src/main.c src/terminal.c ../common/common.c
	gcc -c src/main.c -I headers -o main.o

terminal.o: src/terminal.c
	gcc -c src/terminal.c -I headers -o terminal.o

common.o: ../common/common.c
	gcc -c ../common/common.c -o common.o