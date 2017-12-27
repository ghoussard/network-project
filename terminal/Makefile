all: main.o terminal.o utils.o
	gcc main.o terminal.o utils.o -o terminal
	rm *.o

main.o: src/main.c src/terminal.c ../libs/utils/utils.c
	gcc -c src/main.c -I headers -o main.o

terminal.o: src/terminal.c
	gcc -c src/terminal.c -I headers -o terminal.o

utils.o:  ../libs/utils/utils.c
	gcc -c ../libs/utils/utils.c -o utils.o