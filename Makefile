all: huffman.o
	gcc -O3 huffman.o -lviriatum -o huffman

huffman.o: src/huffman/huffman.c
	gcc -c src/huffman/huffman.c

install: all
	cp huffman /usr/bin

clean:
	rm -f huffman.o
