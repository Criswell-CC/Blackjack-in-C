typedef struct Game {

    void (*StartGame)();
    void (*PlayGame)(int* money);

} Game;

typedef void (*StartGame)();
typedef void (*PlayGame)(int* money);

void Start(bool* in_play);
void SetBet(int* bet, int* money);
void DealCards(int deck[], int *player_hand, int *dealer_hand);
void PrintHandTotal(int sum);
void PrintMoney(int money);
int FindHandTotal(int hand[], int hand_count);
void PrintPlayerHand(int hand[], int hand_count);
void PrintDealerHand(int hand[], int hand_count_dealer);
void NewCardPlayer(int deck[], int *hand, int hand_count_player, int hand_count_dealer);
void NewCardDealer(int deck[], int *hand, int hand_count_player, int hand_count_dealer);
void CheckBlackjacks(bool* game_over, int sum_dealer, int sum_player, int* dealer_hand, int hand_count_dealer, int* money, int bet);
void Hit(int* deck, bool *done_hitting, bool *game_over, int* player_hand, int *hand_count_player, int hand_count_dealer, int sum_player);
void DealerHit(int* deck, int* dealer_hand, int sum_dealer, int sum_player, int hand_count_dealer, int hand_count_player, int* money, int bet);
void Play(int* money);
