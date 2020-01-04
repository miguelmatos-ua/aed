#include "sList.h"
#include <iostream>

#ifndef PROJ_HASH_H
#define PROJ_HASH_H

using namespace std;

class Hash {
    int BUCKET;

    sList<char *> *table;
public:
    Hash(int V);

    void insertItem(char *x);

    void deleteItem(char *key);

    unsigned int hashFunction(const char *str) {
        static unsigned int hash_table[256];
        unsigned int crc, i, j;

        if (hash_table[1] == 0u) {
            for (i = 0u; i < 256u; i++)
                for (hash_table[i] = i, j = 0u; j < 8u; j++)
                    if (hash_table[i] & 1u)
                        hash_table[i] = (hash_table[i] >> 1) ^ 0xAED00022u;
                    else
                        hash_table[i] >>= 1;
        }
        crc = 0xAED02019u; // initial value (chosen arbitrarily)
        while (*str != '\0')
            crc = (crc >> 8) ^ hash_table[crc & 0xFFu] ^ ((unsigned int) *str++ << 24);
        return crc % BUCKET;
    }

    void displayHash();
};

Hash::Hash(int V) { this->BUCKET = V; }

void Hash::insertItem(char *x) {
    int index = hashFunction(x);
    printf("%s --> Hash: %d --> %d\n", x, index, table[index].position());
}

void Hash::deleteItem(char *key) {
    int index = hashFunction(key);

    table[index].search(key);
    table[index].remove();
}

void Hash::displayHash() {
    for (int i = 0; i < BUCKET; i++) {
        printf("%d ", i);
        for (int j = 0; j < table[i].size(); j++) {
            table[i].move(j);
            printf(" --> %s", table[i].value());
        }
        printf("\n");
    }
}

#endif //PROJ_HASH_H
