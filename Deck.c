#include <time.h>

#include "Deck.h"

void Build(int* deck) {

    int i;

    for (i = 0; i < 52; i++) {
        deck[i] = i;
    }
}

void Shuffle(int *deck) {

    srand(time(NULL));

    for (int i = 0; i < 1000; i++) {

        int from = rand() % 52;
        int to = rand() % 52;
        int card = deck[from];

        deck[from] = deck[to];
        deck[to] = card;

    }
}
