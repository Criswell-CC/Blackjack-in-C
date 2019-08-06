#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Game.h"
#include "Deck.h"

char *suits_str[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};

char *faces_str[13] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
            "Ten", "Jack", "Queen", "King", "Ace"};

void Start(bool* in_play) {

    char input = '\n';
    printf("Are you ready to play? 'Y' or 'N'?\n");

    while (toupper(input) != 'Y') {

        scanf("%c", &input);

        if (toupper(input) == 'N') {

            printf("Thanks for playing\n");
            (*in_play) = false;
            fflush(stdin);
            break;

        }

        else if (toupper(input) == 'Y') {

            in_play = true;
            fflush(stdin);

        }

        else {

            printf("Input error. Try again.\n\n");
            fflush(stdin);

        }
    }
}

void SetBet(int* bet, int* money) {

    int input;

    printf("\nMoney: %i\n", *money);
    printf("Make your wager: ");
    scanf("%i", &input);

    *bet = input;

    fflush(stdin);

}

void DealCards(int deck[], int *player_hand, int *dealer_hand) {

     int card1 = deck[0];
     player_hand[0] = card1;

     int card2 = deck[1];
     dealer_hand[0] = card2;

     int card3 = deck[2];
     player_hand[1] = card3;

     int card4 = deck[3];
     dealer_hand[1] = card4;

     printf("\nYour hand: %s of %s, %s of %s\n", faces_str[(player_hand[0]%13)], suits_str[(player_hand[0]/13)], faces_str[(player_hand[1]%13)], suits_str[(player_hand[1]/13)]);
     printf("Dealer hand: ?, %s of %s\n\n", faces_str[(dealer_hand[1]%13)], suits_str[(dealer_hand[1]/13)]);

}

void PrintHandTotal(int sum) {

    printf("Total is: %i\n\n", sum);

}

void PrintMoney(int money) {

    printf("Money: %i\n", money);

}

int FindHandTotal(int hand[], int hand_count) {

    int i, num_aces = 0;
    int sum = 0;

    for (i = 0; i < hand_count ; i++) {
        if (hand[i] % 13 == 12) {
            num_aces++;
            if (sum + (hand[i] % 13) < 22)
            sum = sum + 11;
            else if (sum + (hand[i] % 13) > 21) {
                sum = sum + 1;
            }
        }
        else if ((hand[i] % 13) > 8 && (hand[i] % 13) < 12) {
            sum = sum + 10;
        }
        else {
            sum = sum + ((hand[i] % 13) + 2);
        }
    }

    while (num_aces > 0 && sum > 21) {
        sum = sum - 10;
        num_aces--;
    }

    return sum;
}

void PrintPlayerHand(int hand[], int hand_count) {

    int i;

    printf("Your hand is: ");

    for (i = 0; i < hand_count - 1; i++) {
        printf("%s of %s, ", faces_str[(hand[i]%13)], suits_str[(hand[i]/13)]);
    }

    i = hand_count - 1;

    printf("and %s of %s.\n", faces_str[(hand[i]%13)], suits_str[(hand[i]/13)]);

}

void PrintDealerHand(int hand[], int hand_count_dealer) {

    int i;

    printf("Dealer hand is: ");

    for (i = 0; i < hand_count_dealer - 1; i++) {
        printf("%s of %s, ", faces_str[(hand[i]%13)], suits_str[(hand[i]/13)]);
    }

    i = hand_count_dealer - 1;

    printf("and %s of %s.\n", faces_str[(hand[i]%13)], suits_str[(hand[i]/13)]);
}

void NewCardPlayer(int deck[], int *hand, int hand_count_player, int hand_count_dealer) {

       int card = deck[hand_count_player + hand_count_dealer];
       hand[hand_count_player] = card;

       printf("New card is: %s of %s\n", faces_str[card%13], suits_str[card/13]);

}

void NewCardDealer(int deck[], int *hand, int hand_count_player, int hand_count_dealer) {

       int card = deck[hand_count_player + hand_count_dealer];
       hand[hand_count_dealer] = card;

       printf("New card is: %s of %s\n", faces_str[card%13], suits_str[card/13]);

}

void CheckBlackjacks(bool* game_over, int sum_dealer, int sum_player, int* dealer_hand, int hand_count_dealer, int* money, int bet) {

    if (sum_dealer == 21 && sum_player == 21) {
        PrintDealerHand(dealer_hand, hand_count_dealer);
        printf("Two blackjacks!\n\n");
        (*game_over) = true;
    }

    else if (sum_dealer == 21 && sum_player != 21) {
        PrintDealerHand(dealer_hand, hand_count_dealer);
        printf("Dealer has blackjack!\n\n");
        (*game_over) = true;
    }

    else if (sum_dealer != 21 && sum_player == 21) {
        printf("Blackjack! Congratulations.\n\n");
        (*money) = (*money) + ((bet*3)/2);
        (*game_over) = true;
    }

    else
        return;

}

void Hit(int* deck, bool *done_hitting, bool *game_over, int* player_hand, int *hand_count_player, int hand_count_dealer, int sum_player) {

    char hit = '\n';

    printf("Do you want a new card?\n\n");
    scanf("%c", &hit);

    if (toupper(hit) == 'Y') {

        NewCardPlayer(deck, player_hand, (*hand_count_player), hand_count_dealer);
        (*hand_count_player)++;

        PrintPlayerHand(player_hand, (*hand_count_player));

        sum_player = FindHandTotal(player_hand, (*hand_count_player));
        PrintHandTotal(sum_player);

        fflush(stdin);

        if (sum_player == 21) {

            printf("21!\n\n");
            (*done_hitting) = true;
            (*game_over) = true;

        }

        else if (sum_player > 21) {
            printf("Bust! You lose.\n\n");
            (*done_hitting) = true;
            (*game_over) = true;
        }

        else {

            (*done_hitting) = false;

        }
    }

    else if (toupper(hit) == 'N') {

        (*done_hitting) = true;
        fflush(stdin);

    }

    else {

        printf("Input error.\n\n");
        fflush(stdin);
        scanf("%c", &hit);
        fflush(stdin);
    }
}

void DealerHit(int* deck, int* dealer_hand, int sum_dealer, int sum_player, int hand_count_dealer, int hand_count_player, int* money, int bet) {

    if (sum_dealer < 17) {

        while (sum_dealer < 17) {

            NewCardDealer(deck, dealer_hand, hand_count_player, hand_count_dealer);
            hand_count_dealer++;
            PrintDealerHand(dealer_hand, hand_count_dealer);
            sum_dealer = FindHandTotal(dealer_hand, hand_count_dealer);
            PrintHandTotal(sum_dealer);
        }
    }

    if (sum_dealer > 21) {

        printf("Dealer busts! You win.\n\n");
        money = money + (bet*2);

    }

    if (sum_dealer > sum_player && sum_dealer < 22) {

        printf("You lose!\n\n");

    }

    if (sum_dealer == sum_player) {

        printf("Push!\n\n");

    }

    if (sum_dealer == 21 && sum_player != 21) {

        printf("Dealer got to 21.");

    }

    if (sum_dealer < sum_player) {

        printf("You win!\n\n");
        money = money + (bet*2);

    }
}


void Play(int* money) {

        bool game_over = false;

        int deck[52];

        Deck deck_struct;
        deck_struct.BuildDeck = &Build;
        deck_struct.BuildDeck(deck);

        int player_hand[10];
        int dealer_hand[10];

        memset(player_hand, 0, 10*sizeof(player_hand[0]));
        memset(dealer_hand, 0, 10*sizeof(dealer_hand[0]));

        int sum_player = 0;
        int sum_dealer = 0;
        int hand_count_player = 2;
        int hand_count_dealer = 2;

        int bet = 0;
        SetBet(&bet, money);
        (*money) = (*money) - bet;

        deck_struct.ShuffleDeck = &Shuffle;
        deck_struct.ShuffleDeck(deck);

        DealCards(deck, player_hand, dealer_hand);

        sum_player = FindHandTotal(player_hand, hand_count_player);
        sum_dealer = FindHandTotal(dealer_hand, hand_count_dealer);

        PrintHandTotal(sum_player);

        CheckBlackjacks(&game_over, sum_dealer, sum_player, dealer_hand, hand_count_dealer, money, bet);

        if (!game_over) {

            bool done_hitting = false;

            while (!done_hitting) {

                Hit(deck, &done_hitting, &game_over, player_hand, &hand_count_player, hand_count_dealer, sum_player);

            }
        }

        if (!game_over) {

            PrintDealerHand(dealer_hand, hand_count_dealer);
            PrintHandTotal(sum_dealer);
            DealerHit(deck, dealer_hand, sum_dealer, sum_player, hand_count_dealer, hand_count_player, money, bet);

        }
}
