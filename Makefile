install: all
	cp huffman /usr/bin

all: huffman.o
	gcc -O3 huffman.o -lviriatum -o huffman

huffman.o: src/huffman/huffman.c
	gcc -c src/huffman/huffman.c

clean:
	rm -f huffman.o
