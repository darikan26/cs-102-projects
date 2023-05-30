CFLAGS=-Wall -Werror -Wfatal-errors

main: main.o stack.o node.o
	g++ -o main main.o stack.o node.o

main.o: main.cpp stack.h node.h
	g++ -c $(CFLAGS) main.cpp

stack.o: stack.cc stack.h node.o
	g++ -c $(CFLAGS) stack.cc

node.o: node.cc node.h
	g++ -c $(CFLAGS) node.cc

clean:
	rm -rf *.o main
