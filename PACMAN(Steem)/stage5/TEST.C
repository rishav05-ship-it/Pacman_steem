#include <stdio.h>
#include "EVENTS.C"

int main()
{
    Model game;
    int key = 0;

    printf("=== MODEL TEST DRIVER START ===\n");

    game.pacman.x = 10;
    game.pacman.y = 10;
    game.pacman.dx = 1;
    game.pacman.dy = 0;
    game.score_board.life_count = 3;

    game.ghosts[0].x = 12;
    game.ghosts[0].y = 10;

    printf("Initial Pacman pos: (%d, %d)\n", game.pacman.x, game.pacman.y);
    move_pacman(&game.pacman);
    printf("After move: (%d, %d)\n", game.pacman.x, game.pacman.y);

    game.ghosts[0].x = game.pacman.x;
    game.ghosts[0].y = game.pacman.y;

    if (check_collision(&game.pacman, &game.ghosts[0]) != 0)
        printf("Collision detected!\n");
    else
        printf("No collision.\n");

    game.score_board.life_count = 0;
    if (check_game_over(&game.score_board))
        printf("Game over!\n");
    else
        printf("Still alive.\n");

    key = 0x01;
    if (check_exit_request(key))
        printf("Exit requested!\n");
    else
        printf("Continue playing.\n");

    printf("=== MODEL TEST DRIVER END ===\n");
    return 0;
}
