#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <stdbool.h>
#include <locale.h>

#include <uchar.h>

//A node of our beloved Huffman Tree
typedef struct symb{
    char16_t symbol;
    int freq;
    struct symb *left;
    struct symb *right;
} SYMBOL;

//A priority queue based on min-heap
typedef struct queue{
    int size;
    SYMBOL** heap;
} QUEUE;

//A Huffman code for a symbol
typedef struct hm_code{
    char16_t symb;
    unsigned long long code;
    int size;
} HM_CODE;

//A bit stream, buffer cont. up to 16 bits
typedef struct bitstream{
    FILE* file;
    char16_t buffer;
    long long count;
} BITSTREAM;

//Creating a node for the Huffman tree
SYMBOL* create_node(char16_t symb, unsigned freq, SYMBOL* left, SYMBOL* right){
    SYMBOL* character = malloc(sizeof(SYMBOL));

    character->freq = freq;
    character->symbol = symb;
    character->left = left;
    character->right = right;

    return character;
}

//Creating a priority queue of nodes
QUEUE* create_queue(){
    QUEUE* queue = malloc(sizeof(QUEUE));

    if (!queue) {
        perror("Failed to allocate memory for: queue");
        exit(EXIT_FAILURE);
    }

    queue->size = 0;
    queue->heap = NULL;
    return queue;
}

//Creating a bit stream
BITSTREAM* create_stream(FILE* file){
    BITSTREAM* stream = malloc(sizeof(BITSTREAM));

    if (!stream) {
        perror("Failed to allocate memory for: bit_stream");
        exit(EXIT_FAILURE);
    }

    stream->count = 0;
    stream->buffer = 0;
    stream->file = file;

    return stream;
}

//Adding a symbol to the priority queue
void add_symbol (QUEUE* queue, SYMBOL* node) {
    queue->heap = realloc(queue->heap, (queue->size + 1) * sizeof(SYMBOL*));

    if (!queue->heap) {
        puts("Failed to allocate memory for: heap");
        exit(0);
    }
    ++queue->size;

    int idx = queue->size - 1;

    while (idx > 0 && node->freq >= queue->heap[idx - 1]->freq) {
        queue->heap[idx] = queue->heap[idx - 1];
        idx--;
    }
    queue->heap[idx] = node;
}

void swap(SYMBOL** a, SYMBOL** b){
    SYMBOL* temp = *a;
    *a = *b;
    *b = temp;
}

//Filling the queue with nodes
QUEUE* queue_fill(FILE* input) {
    QUEUE* queue = create_queue();

    char16_t symb;

    fseek(input, 0, SEEK_END);
    long numBytes = ftell(input);
    rewind(input);

    for (int i = 0; i < (numBytes / sizeof(char16_t)); i++) {
        bool in_heap = false;
        symb = fgetwc(input);

        // Checking for the presence of a symbol in the queue
        for (int j = 0; j < queue->size; j++){
            if (queue->heap[j]->symbol == symb) {
                queue->heap[j]->freq++;

                // Sorting
                while (j > 0 && queue->heap[j]->freq >= queue->heap[j - 1]->freq) {
                    swap(&queue->heap[j], &queue->heap[j]-1);
                    j--;
                }

                in_heap = true;
                break;
            }
        }
        if (!in_heap){
            SYMBOL* node = create_node(symb, 1, NULL, NULL);
            add_symbol(queue, node);
        }
    }
    rewind(input);
    return queue;
}

//Creating the Huffman tree
SYMBOL* create_huffman_tree(QUEUE* queue){
    while (queue->size > 1) {
        SYMBOL* left = queue->heap[--queue->size];
        SYMBOL* right = queue->heap[--queue->size];
        SYMBOL* new_node = create_node(0, left->freq + right->freq, left, right);
        add_symbol(queue, new_node);
    }
    return queue->heap[0];
}

//Writing bits to the output file
void write_bit(BITSTREAM* stream, bool bit){
    if (stream->count == 8){ //на BIT заменить?
        fwrite(&(stream->buffer), sizeof(char), 1, stream->file);
        stream->buffer = 0;
        stream->count = 0;
    }

    stream->buffer = bit | (stream->buffer << 1);
    ++stream->count;
}


//Writing a symbol to the output file bit-by-bit
void write_symbol(BITSTREAM* stream, char16_t symb) {
    for (int i = 15; i >= 0; i--){
        bool bit = (symb >> i) & 1;
        write_bit(stream, bit);
    }
}

//Writing nodes of the Huffman tree to the file
void write_tree(SYMBOL* root, BITSTREAM* stream){
    if (!root->left){
        write_bit(stream, 1);
        write_symbol(stream, root->symbol);
        return;
    }
    write_bit(stream, 0);
    write_tree(root->left, stream);
    write_tree(root->right, stream);

}

//Building a Huffman code structure
HM_CODE create_code(char16_t symb, int size, long long code){
    HM_CODE codes;

    codes.symb = symb;
    codes.size = size;
    codes.code = code;

    return codes;
}

//Inserting nodes of the Huffman tree
void get_code(SYMBOL* node, HM_CODE* codes, long long symb_code, int size, int* idx) {
    if (!node->left) {
        codes[(*idx)] = create_code(node->symbol, size, symb_code);
        ++(*idx);
        return;
    }
    get_code(node->left, codes, symb_code << 1, size + 1, idx);
    get_code(node->right, codes, (symb_code << 1) | 1, size + 1, idx);
}

//Writing output data
void write_data(HM_CODE* codes_arr, char16_t symb, BITSTREAM* stream, int size){
    int i;
    for (i = 0; i < size; i++){
        if (codes_arr[i].symb == symb){
            break;
        }
    }
    for (int j = codes_arr[i].size - 1; j >= 0; j--){
        bool bit = (codes_arr[i].code >> j) & 1;
        write_bit(stream, bit);
    }
}

void compression(char* in_name, char* out_name){
    FILE* input = fopen(in_name, "rb");
    FILE* output = fopen(out_name, "wb");

    if (!input){
        perror("No input file!");
        exit(0);
    }

    //Creating and filling a priority queue
    QUEUE* queue = queue_fill(input);

    BITSTREAM* stream = create_stream(output);
    HM_CODE* codes_arr = malloc(queue->size * sizeof(HM_CODE));

    //Creating the Huffman tree with queue nodes
    SYMBOL* root = create_huffman_tree(queue);

    //Writing the length and Huffman tree nodes to the output
    fwrite(&(root->freq), sizeof(int), 1, stream->file);
    write_tree(root, stream);


    int idx = 0;
    get_code(root, codes_arr, 0, 0, &idx);

    fseek(input, 0, SEEK_END);
    long num_bytes = ftell(input);
    rewind(input);

    //Encoding of symbols and writing to the output file
    char16_t symb;
    for (int i = 0; i < num_bytes/sizeof(char16_t); i++){
        symb = fgetwc(input);
        write_data(codes_arr, symb, stream, idx);
    }

    //Clearing the buffer
    stream->buffer = stream->buffer << (8 - stream->count);
    fwrite(&(stream->buffer), sizeof(char), 1, stream->file);

    //Clearing the memory
    for (int i = 0; i < queue->size; i++) {
        free(queue->heap[i]);
    }
    free(queue->heap);
    free(queue);
    free(stream);
    free(codes_arr);

    fclose(input);
    fclose(output);
}

int read_bit(BITSTREAM *stream) {
    int bit;
    if (stream->count == 0) {
        if (fread(&stream->buffer, sizeof(char), 1, stream->file) != 1)
            return -1;
        stream->count = 8;
    }
    --stream->count;
    bit = (stream->buffer >> stream->count) & 1;
    return bit;
}

//Recreating symbols bit-by-bit
int read_symbol(char16_t *symbol, BITSTREAM *stream) {
    *symbol = 0;
    for (int i = 0; i < 16; i++) {
        *symbol = *symbol << 1;
        int bit = read_bit(stream);
        if (bit == -1)
            return -1;
        *symbol = *symbol | bit;
    }
    return 0;
}

//Recreating the Huffman tree
SYMBOL *get_tree(BITSTREAM *stream) {
    int bit = read_bit(stream);
    if (bit == -1)
        return NULL;
    if (bit == 1) {
        char16_t symbol;
        if (read_symbol(&symbol, stream) == -1)
            return NULL;
        return create_node(symbol, 0, NULL, NULL);
    }
    SYMBOL *left = get_tree(stream);
    SYMBOL *right = get_tree(stream);
    return create_node('$', 0, left, right);
}

int uncomp(SYMBOL *root, BITSTREAM *stream, char16_t *symbol) {
    SYMBOL *cur = root;
    while (cur->left) {
        int bit = read_bit(stream);
        if (bit == -1) //Условие на остановку декодировки
            return -1;
        if (bit == 0)
            cur = cur->left;
        else
            cur = cur->right;
    }
    *symbol = cur->symbol;
    return 1;
}

void decompress(char* in_name, char* out_name) {
    FILE *input = fopen(in_name, "rb");
    FILE *output = fopen(out_name, "wb");

    BITSTREAM *stream = create_stream(input);

    int length;
    fread(&length, sizeof(int), 1, input);

    SYMBOL *root = get_tree(stream);

    //Writing decoded symbols to the output file
    for (int i = 0; i < length; i++) {
        char16_t symbol;
        int check = uncomp(root, stream, &symbol);
        if (check == -1) {
            fclose(stream->file);
            return;
        }
        fwrite(&symbol, sizeof(char16_t), 1, output);
    }

    //Clearing the memory
    free(stream);
    free(root);

    fclose(input);
    fclose(output);
}

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "");

    char* operation = argv[1];
    char* input_file = argv[2];
    char* output_file = argv[3];

    if (!strcmp(operation, "c")) {
        compression(input_file, output_file);
    } else if (!strcmp(operation, "d")) {
        decompress(input_file, output_file);
    } else {
        perror("Operation unknown");
        return 1;
    }

    return 0;
}