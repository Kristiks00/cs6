all: program
main.o: main.c
	gcc -m32 -no-pie -std=c99 -c -o main.o main.c
root.o: root.c
	gcc -m32 -no-pie -std=c99 -c -o root.o root.c
integral.o: integral.c
	gcc -m32 -no-pie -std=c99 -c -o integral.o integral.c
debug.o: debug.c
	gcc -m32 -no-pie -std=c99 -c -o debug.o debug.c
func.o: func.asm
	nasm -f elf32 -o func.o func.asm
program: main.o root.o integral.o debug.o func.o
	gcc -m32 -no-pie -o program main.o root.o integral.o debug.o func.o
clean:
	rm -rf *.o program
