any: main.o utils.o tetramino.o 
	g++ -lpthread -pthread -o .\bin\Tetris utils.o tetramino.o main.o

main.o : .\src\main.cpp
	g++ -c .\src\main.cpp

utils.o : .\lib\utils.cpp
	g++ -c .\lib\utils.cpp

tetramino.o : .\lib\tetramino.cpp
	g++ -c .\lib\tetramino.cpp

clean:
	del .\bin\*.exe
	del .\*.o
rebuild:
	make clean
	make