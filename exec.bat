mkdir bin
cd src
gcc -c verifyChar.c -o ../bin/verifyChar.o && gcc -c codeGeneration.c -o ../bin/codeGeneration.o && gcc -c symbol.c -o ../bin/symbol.o && gcc -c error.c -o ../bin/error.o && gcc -c token.c -o ../bin/token.o && gcc -c lexic.c -o ../bin/lexic.o &&  gcc -c syntatic.c -o ../bin/syntatic.o && gcc -c main.c -o ../bin/main.o
cd ../bin
gcc *.o -o ../compiler