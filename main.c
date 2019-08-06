#include <stdbool.h>

#include "Game.h"

int main() {

    Game game;
    game.StartGame = &Start;
    game.PlayGame = &Play;

    bool in_play = true;

    int money = 500;

    while (in_play) {

        game.StartGame(&in_play);

        if (in_play)
            game.PlayGame(&money);

    }

    return 0;
}
