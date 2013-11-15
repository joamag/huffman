#include <stdio.h>
#include <stdlib.h>
#include <viriatum_commons/viriatum_commons.h>

int main(int argc, char *argv[]) {
    char *in_path;
    char out_path[PATH_MAX];
    char dec_path[PATH_MAX];
    struct file_stream_t *in_stream;
    struct file_stream_t *out_stream;
    struct huffman_t *huffman;
    clock_t initial;
    clock_t delta;
    float delta_f;

    if(argc < 2) {
        printf("Usage: huffman <input> [output]\n");
        exit(1);
    }

    in_path = argv[1];

    if(argc == 2) {
        sprintf(out_path, "%s.huffman", in_path);
    } else {
        sprintf(out_path, "%s", argv[2]);
    }

    sprintf(dec_path, "%s.decoded", in_path);

    initial = clock();

    create_file_stream(
        &in_stream,
        (unsigned char *) in_path,
        (unsigned char *) "rb"
    );

    create_file_stream(
        &out_stream,
        (unsigned char *) out_path,
        (unsigned char *) "wb"
    );

    create_huffman(&huffman);
    generate_table_huffman(huffman, in_stream->stream);
    generate_prefix_huffman(huffman);

    encode_huffman(huffman, in_stream->stream, out_stream->stream);

    delete_file_stream(out_stream);
    delete_file_stream(in_stream);

    delta = clock() - initial;
    delta_f = ((float) delta) / CLOCKS_PER_SEC;

    printf("Encoded '%s' into '%s' in %.2f seconds\n", in_path, out_path, delta_f);

    initial = clock();

    create_file_stream(
        &in_stream,
        (unsigned char *) out_path,
        (unsigned char *) "rb"
    );

    create_file_stream(
        &out_stream,
        (unsigned char *) dec_path,
        (unsigned char *) "wb"
    );

    decode_huffman(huffman, in_stream->stream, out_stream->stream);

    delete_file_stream(out_stream);
    delete_file_stream(in_stream);

    delete_huffman(huffman);

    delta = clock() - initial;
    delta_f = ((float) delta) / CLOCKS_PER_SEC;

    printf("Decoded '%s' into '%s' in %.2f seconds\n", out_path, dec_path, delta_f);
    
    exit(0);
}
