system.out: main.o contactbst.o myvector.o contact.o 
	g++ main.o contactbst.o myvector.o contact.o -o system.out
main.o: main.cpp
	g++ -c main.cpp
contactbst.o: contactbst.cpp contactbst.h
	g++ -c contactbst.cpp
myvector.o: myvector.cpp myvector.h
	g++ -c myvector.cpp
contact.o: contact.cpp contact.h
	g++ -c contact.cpp
clean:
	rm *.o *.out