cd VirtualMachine
gcc -c instruction.c -o instruction.o && gcc -c stack.c -o stack.o && gcc -c main.c -o main.o
gcc *.o -o ../vm