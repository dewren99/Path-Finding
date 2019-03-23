
all:	king king-moves rook-moves

king:	 king.o mapio.o
	g++ -std=c++0x -o king king.o mapio.o

king-moves:	 king-moves.o mapio.o
	g++ -std=c++0x -o king-moves king-moves.o mapio.o

rook-moves:	 rook-moves.o mapio.o
	g++ -std=c++0x -o rook-moves rook-moves.o mapio.o

king.o:	 king.cpp mapio.h
	g++ -std=c++0x -c king.cpp

king-moves.o:	 king-moves.cpp mapio.h
	g++ -std=c++0x -c king-moves.cpp

rook-moves.o:	 rook-moves.cpp mapio.h
	g++ -std=c++0x -c rook-moves.cpp

mapio.o:	 mapio.cpp mapio.h
	g++ -std=c++0x -c mapio.cpp

clean:	
	rm -f core a.out *.o king king-moves rook-moves


