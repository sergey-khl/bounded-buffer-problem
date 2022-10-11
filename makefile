prodcon: main.o helper.o
	g++ -g -o prodcon main.o helper.o 

helper.o: helper.cpp helper.h
	g++ -c helper.cpp -o helper.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm ./*o ./prodcon