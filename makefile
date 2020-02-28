

sfml = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

main: main.cpp QTree.h
	g++ -g -o main.o main.cpp QTree.h $(sfml)
