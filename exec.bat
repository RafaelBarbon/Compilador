gcc -c token.c -o token.o && gcc -c lexico.c -o lexico.o
gcc token.o lexico.o -o compilador