any: main.o utils.o tetramino.o
	g++ -lpthread -pthread -o Tetris main.o tetramino.o utils.o

main.o : main.cpp
	g++ -c main.cpp

utils.o : utils.cpp
	g++ -c utils.cpp

tetramino.o : tetramino.cpp
	g++ -c tetramino.cpp

clean:
	del *.exe
	del *.o
rebuild:
	make clean
	make