#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MIN_SIZE 100
#define MAX_SIZE 20000
#define LOAD 0.9
#define GROATH 2

//
// FILE MANAGEMENT
//
typedef struct file_data {
    long word_pos; /* Word position */
    long word_num; /* Word number */
    char word[64];
    FILE *fp;
    long current_pos; /* Current position */

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
//
// END FILE MANAGEMENT
//

//
// HASH
//
unsigned int hash_function(const char *str, unsigned int s) {
    static unsigned int table[256];
    unsigned int crc, i, j;

    if (table[1] == 0u) {
        for (i = 0u; i < 256u; i++)
            for (table[i] = i, j = 0u; j < 8u; j++)
                table[i] & 1u ? (table[i] = (table[i] >> 1) ^ 0xAED00022u) : (table[i] >>= 1);
    }
    crc = 0xAED02019u; // initial value (chosen arbitrarily)
    while (*str != '\0')
        crc = (crc >> 8) ^ table[crc & 0xFFu] ^ ((unsigned int) *str++ << 24);
    return crc % s;
}

typedef struct node_words {
    char word[64];
    int times;
    long first_pos;
    long last_pos;
    long small;
    long large;
    long total_distance; //necessary to calculate avg
    struct node_words *next;
} node_words;

typedef struct hash_data {
    unsigned long size;
    unsigned long ocupation;
    node_words **node;
} hash_data;

void resize(hash_data *hashData);

node_words *new_node_words(const char *word, long word_pos) {
    node_words *node = (node_words *) malloc(sizeof(node_words));
    if (node == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    strcpy(node->word, word);
    node->times = 1;
    node->last_pos = word_pos;
    node->first_pos = word_pos;
    node->small = LONG_MAX;
    node->large = -1;
    node->next = NULL;

    return node;
}

hash_data *new_hash_data(unsigned long size) {
    hash_data *hd = (hash_data *) malloc(sizeof(hash_data));
    if (hd == NULL || (hd->node = malloc(sizeof(node_words *) * size)) == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        hd->node[i] = NULL;
    }

    hd->size = size;
    hd->ocupation = 0;

    return hd;
}

void free_hash_table(hash_data *hd) {
    if (hd == NULL) return;

    node_words *list, *temp_list;

    for (int i = 0; i < hd->size; i++) {
        list = hd->node[i];
        while (list != NULL) {
            temp_list = list;
            list = list->next;

            free(temp_list->word);
            free(temp_list);
        }

        free(hd->node);
        free(hd);
    }
}

node_words *find(hash_data *hd, const char *word) {
    node_words *nodeWords;

    unsigned int index = hash_function(word, hd->size);

    for (nodeWords = hd->node[index];
         nodeWords != NULL && strcmp(nodeWords->word, word) != 0; nodeWords = nodeWords->next);

    return nodeWords;
}

void insert(const char *word, node_words *node, hash_data *hashData) {
    unsigned int i = hash_function(word, hashData->size);
    node_words *tmp;

    if (hashData->node[i] == NULL) {
        hashData->node[i] = node;
    } else {
        tmp = hashData->node[i];
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
    node->next = NULL;

    hashData->ocupation++;

    if ((int) hashData->ocupation > (int) hashData->size * LOAD && hashData->size < MAX_SIZE) // if it's 90% full
        resize(hashData);
}

void resize(hash_data *hashData) {
    hash_data *new_hash = new_hash_data(hashData->size * GROATH);

    for (int i = 0; i < hashData->size; i++) {
        node_words *nw = hashData->node[i];

        while (nw != NULL) {
            node_words *next = nw->next;
            insert(nw->word, nw, new_hash);
            nw = next;
        }
    }

    //free the memory
    free(hashData->node);
    *hashData = *new_hash;
    free(new_hash);
}

void stats(node_words *nodeWords, const char *word, long word_pos) {
    long dist = word_pos - nodeWords->last_pos;
    nodeWords->total_distance += dist;

    if (nodeWords->small > dist)
        nodeWords->small = dist;
    if (nodeWords->large < dist)
        nodeWords->large = dist;

    nodeWords->times++;
    nodeWords->last_pos = word_pos;
}

void display_hash(hash_data *hd) {
    for (int i = 0; i < hd->size; i++) {
        printf("%d: ", i);
        node_words *tmp = hd->node[i];
        while (tmp != NULL) {
            double avg = (double) tmp->total_distance / (tmp->times - 1);

            if (tmp->small == LONG_MAX) {
                tmp->small = -1;
                tmp->large = -1;
                printf("%s [count:%d, first:%ld, last:%ld] --> ", tmp->word, tmp->times, tmp->first_pos,
                       tmp->last_pos);
            } else {
                printf("%s [count:%d, first:%ld, last:%ld, min:%ld, max:%ld, avg:%.2f] --> ", tmp->word, tmp->times,
                       tmp->first_pos, tmp->last_pos, tmp->small, tmp->large, avg);
            }

            tmp = tmp->next;
        }
        printf("NULL\n");
    }
}


int main(int argc, char **argv) {
    char *filename;
    if (argc > 1)
        filename = argv[1];
    else
        filename = "/home/mcmatos/CLionProjects/ass2/SherlockHolmes.txt";

    file_data_t fd;

    if (open_text_file(filename, &fd) != 0) {
        fprintf(stderr, "unable to open file \"%s\"", filename);
        return 2;
    }

    hash_data *hashData = new_hash_data(MIN_SIZE);
    while (read_word(&fd) == 0) {
        node_words *node = find(hashData, fd.word);
        if (node == NULL) {
            node_words *new_node = new_node_words(fd.word, fd.word_pos);
            insert(fd.word, new_node, hashData);
        } else {
            stats(node, fd.word, fd.word_pos);
        }

    }
    close_text_file(&fd);
    display_hash(hashData);
    free_hash_table(hashData);
    printf("SUCCESS!!!\n");
    return 0;
}
