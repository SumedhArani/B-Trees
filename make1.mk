btree.out: a.out
	mv a.out btree.out
	rm *.o
a.out : client.o node.o btree.o
	g++ -std=c++14 node.o client.o btree.o
node.o : node.cpp node.h
	g++ -c -std=c++14 node.cpp
client.o : client.cpp node.h btree.h
	g++ -c -std=c++14 client.cpp
btree.o : btree.cpp btree.h node.h
	g++ -c -std=c++14 btree.cpp
	