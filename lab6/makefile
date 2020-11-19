

Node: Node.c dusocket.h
	gcc Node.c -L, -lduSocket -o Node

Head: Head.c duSocket.h
	gcc Head.c -L, -lduSocket -o Head

libduSocket.a: duSocket.h duSocket.c
	gcc duSocket.c -c
	ar -cvq libduSocket.a duSocket.o
        rm duSocket.o
clean:
	rm Node
	rm Head
	rm libduSocket.a
