all: huffman.o
        gcc -O3 huffman.o -lviriatum -o huffman

huffman.o: huffman.c
        gcc -c huffman.c

clean:
        rm -f huffman.o
