mkdir bin
cd src
gcc -c token.c -o ../bin/token.o && gcc -c lexico.c -o ../bin/lexico.o
cd ../bin
gcc token.o lexico.o -o ../compilador