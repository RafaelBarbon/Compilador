mkdir bin
cd src
gcc -c error.c -o ../bin/error.o && gcc -c token.c -o ../bin/token.o && gcc -c lexico.c -o ../bin/lexico.o
cd ../bin
gcc *.o -o ../compilador