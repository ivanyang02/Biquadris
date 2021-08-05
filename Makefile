a: main.o board.o window.o block.o cell.o iblock.o jblock.o lblock.o oblock.o sblock.o zblock.o tblock.o
	g++ -Werror=vla main.o board.o window.o block.o cell.o iblock.o jblock.o lblock.o oblock.o sblock.o zblock.o tblock.o -o a -lX11

main.o: main.cc
	g++ -c main.cc

board.o: board.cc board.h
	g++ -c board.cc

window.o: window.cc window.h
	g++ -c window.cc

block.o: block.cc block.h
	g++ -c block.cc

cell.o: cell.cc cell.h
	g++ -c cell.cc

iblock.o: iblock.cc iblock.h
	g++ -c iblock.cc

jblock.o: jblock.cc jblock.h
	g++ -c jblock.cc

lblock.o: lblock.cc lblock.h
	g++ -c lblock.cc

oblock.o: oblock.cc oblock.h
	g++ -c oblock.cc

sblock.o: sblock.cc sblock.h
	g++ -c sblock.cc

zblock.o: zblock.cc zblock.h
	g++ -c zblock.cc

tblock.o: tblock.cc tblock.h
	g++ -c tblock.cc

