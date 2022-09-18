mkdir bin
cd src
gcc -c verifyChar.c -o ../bin/verifyChar.o && gcc -c symbol.c -o ../bin/symbol.o && gcc -c error.c -o ../bin/error.o && gcc -c token.c -o ../bin/token.o && gcc -c lexico.c -o ../bin/lexico.o && gcc -c main.c -o ../bin/main.o
cd ../bin
gcc *.o -o ../compilador