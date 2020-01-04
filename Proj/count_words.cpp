#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Hash.h"

typedef struct file_data {
    // public data
    long word_pos; // zero-based
    long word_num; // zero-based
    char word[64];
    // private data
    FILE *fp;
    long current_pos; // zero-based
} file_data_t;

int open_text_file(char *file_name, file_data_t *fd) {
    fd->fp = fopen(file_name, "rb");
    if (fd->fp == NULL)
        return -1;
    fd->word_pos = -1;
    fd->word_num = -1;
    fd->word[0] = '\0';
    fd->current_pos = -1;
    return 0;
}

void close_text_file(file_data_t *fd) {
    fclose(fd->fp);
    fd->fp = NULL;
}

int read_word(file_data_t *fd) {
    int i, c;

    do {
        c = fgetc(fd->fp);
        if (c == EOF)
            return -1;
        fd->current_pos++;
    } while (c <= 32);

    // record word
    fd->word_pos = fd->current_pos;
    fd->word_num++;
    fd->word[0] = (char) c;

    for (i = 1; i < (int) sizeof(fd->word) - 1; i++) {
        c = fgetc(fd->fp);
        if (c == EOF)
            break; // end file
        fd->current_pos++;
        if (c <= 32)
            break; // terminate word
        fd->word[i] = (char) c;
    }
    fd->word[i] = '\0';

    return 0;
}

int main(int argc, char **argv) {
    int opt = -1;
    if (argc >= 3 && strcmp(argv[1], "-a") == 0) opt = 'a'; // all words
    if (argc >= 3 && strcmp(argv[1], "-d") == 0) opt = 'd'; // different words
    if (argc >= 3 && strcmp(argv[1], "-l") == 0) opt = 'l'; // list words
    if (opt < 0) {
        fprintf(stderr, "\e[5;31m"); // blink on (may not work in some text terminals), text in red
        fprintf(stderr, "usage: %s -a text_file ...  # count the number of words\n", argv[0]);
        fprintf(stderr, "       %s -d text_file ...  # count the number of different words\n", argv[0]);
        fprintf(stderr, "       %s -l text_file ...  # list all words\n", argv[0]);
        fprintf(stderr, "\e[0m"); // normal output
        return 1;
    }

    for (int i = 2; i < argc; i++) {
        file_data_t fileData;
        if (open_text_file(argv[i], &fileData) != 0) {
            fprintf(stderr, "unable to open file %s\n", argv[i]);
            return 2;
        }
        Hash hash(25);
        while (read_word(&fileData) == 0) {
            hash.insertItem(fileData.word);
        }
        hash.displayHash();
        close_text_file(&fileData);
    }
}