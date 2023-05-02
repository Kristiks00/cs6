all: program
6_with_link.o: 6_with_link.c
	gcc -m32 -no-pie -std=c99 -c -o 6_with_link.o 6_with_link.c
6_func.o: 6_func.asm
	nasm -f elf32 -o 6_func.o 6_func.asm
program: 6_with_link.o 6_func.o
	gcc -m32 -no-pie -o program 6_with_link.o 6_func.o
clean:
	rm -rf 6_with_link.o 6_func.o program
