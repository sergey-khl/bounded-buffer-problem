prodcon: main.o helper.o transcont.o
	g++ -g -o prodcon main.o transcont.o  helper.o -lpthread

helper.o: helper.cpp helper.h transcont.h
	g++ -c helper.cpp -o helper.o

transcont.o: transcont.cpp transcont.h
	g++ -c transcont.cpp -o transcont.o 

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm ./*o ./prodcon