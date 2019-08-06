typedef struct Deck {

    int* (*BuildDeck)();
    void (*ShuffleDeck)(int *deck);

} Deck;

typedef int* (*BuildDeck)();
typedef void (*ShuffleDeck)(int *deck);

void Build(int* deck);
void Shuffle(int *deck);
