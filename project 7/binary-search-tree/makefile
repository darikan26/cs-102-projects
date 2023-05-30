CFLAGS=-Wall -Werror -Wfatal-errors

main: main.o node.o binarysearchtree.o
	g++ -o main main.o node.o binarysearchtree.o

main.o: main.cc node.h binarysearchtree.h
	g++ -c $(CFLAGS) main.cc

node.o: node.cc node.h
	g++ -c $(CFLAGS) node.cc

binarysearchtree.o: binarysearchtree.cc binarysearchtree.h
	g++ -c $(CFLAGS) binarysearchtree.cc

clean:
	rm -rf *.o main
