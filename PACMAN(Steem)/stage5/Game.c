#include <osbind.h>
#include "POS_STA.h"
#include "model.h"
#include "events.h"
#include "renderer.h"


#define TICK_ADDRESS 0x462   /* Atari 70 Hz clock address */

/* Read 70 Hz timer safely (must use supervisor mode) */
unsigned long get_time(void)
{
    unsigned long *clock = (unsigned long *)TICK_ADDRESS;
    unsigned long old_ssp = Super(0);
    unsigned long t = *clock;
    Super(old_ssp);
    return t;
}

int main()
{
	 /* Direct screen buffer (Physbase) */
    UINT16 *base = Physbase();
    char *cbase  = Physbase();
    unsigned long prev_time, curr_time;
    Model game;
    int key = 0;
    int i;

    /* NEW: ghost timing counter (this is the ONLY change) */
    int ghost_interval = 0;

    /* ------------ INITIAL SETUP ------------ */
    game.pacman.x  = 112;
    game.pacman.y  = 48;
    game.pacman.dx = 0;
    game.pacman.dy = 0;

    game.ghosts[0].x  = 48;
    game.ghosts[0].y  = 48;
    game.ghosts[0].dx = 1;
    game.ghosts[0].dy = 0;
    game.ghosts[0].isScared = 0;
    game.ghosts[0].cooldownTimer = 0;
    game.ghosts[0].points = 200;

    game.ghosts[1].x  = 192;
    game.ghosts[1].y  = 48;
    game.ghosts[1].dx = -1;
    game.ghosts[1].dy = 0;
    game.ghosts[1].isScared = 0;
    game.ghosts[1].cooldownTimer = 0;
    game.ghosts[1].points = 20;

    pellet_locations(&game);

	  /* power pellets */
    for (i = 0; i < 2; i++)
    {
        game.p_pellets[i].x = 16 + (i * (16 * 12));
        game.p_pellets[i].y = 80;
        game.p_pellets[i].isEaten = 0;
        game.p_pellets[i].points = 5;
        game.p_pellets[i].isPower = 1;
    }

    game.score_board.score = 0;
    game.score_board.life_count = 3;

    render(&game, base, cbase);

    prev_time = get_time();

    /* ------------ MAIN GAME LOOP ------------ */
    while (!check_exit_request(key))
    {
		 /* Keyboard input */
        if (Cconis())
        {
            key = Cnecin();
            move_request(&game.pacman, key);
        }

        curr_time = get_time();
        if (curr_time != prev_time)
        {
            prev_time = curr_time;

            /* Update Pac-Man */
            move_pacman(&game.pacman);

			/* Pellet collision checks */
            for (i = 0; i < 42; i++) {
                if (game.pacman.x == game.pellets[i].x &&
                    game.pacman.y == game.pellets[i].y)
                {
                    eat_pellet(&game.pellets[i], &game.score_board,
                               &game.ghosts[0], &game.ghosts[1]);
                }
            }

			 /* Power pellet checks */
            for (i = 0; i < 2; i++) {
                if (game.pacman.x == game.p_pellets[i].x &&
                    game.pacman.y == game.p_pellets[i].y)
                {
                    eat_pellet(&game.p_pellets[i], &game.score_board,
                               &game.ghosts[0], &game.ghosts[1]);
                }
            }

            /* ---------- Ghost movement timing ---------- */
            if (ghost_interval % 10 == 0) {
                for (i = 0; i < 2; i++)
                {
                    if (game.ghosts[i].cooldownTimer == 0)
                    {
                        if (!game.ghosts[i].isScared) {
                            update_ghost(&game.ghosts[i], &game.pacman);
                        }
                        else if (ghost_interval % 20 == 0) {
                            update_ghost(&game.ghosts[i], &game.pacman);
                        }
                    }
                }
            }
            ghost_interval++;
            /* ----------------------------------------- */

			 /* Collision handling (life loss or ghost eaten) */
            for (i = 0; i < 2; i++)
            {
                if (check_collision(&game.pacman, &game.ghosts[i]))
                {
                    if (!game.ghosts[i].isScared &&
                        !game.ghosts[i].cooldownTimer)
                    {
                        lose_life(&game.score_board);
                        reset_game(&game);
                    }
                    else if (game.ghosts[i].isScared)
                    {
                        eat_ghost(&game.ghosts[i], &game.score_board);
                    }
                }

                if (game.ghosts[i].isScared > 0)
                    game.ghosts[i].isScared--;

                if (game.ghosts[i].cooldownTimer > 0)
                    game.ghosts[i].cooldownTimer--;
            }

            if (all_pellets_eaten(&game))
            {
                reset_game(&game);
                pellet_locations(&game);
                for (i = 0; i < 2; i++)
                    game.p_pellets[i].isEaten = 0;
            }

			/* Reset full game if out of lives */
            if (game.score_board.life_count == 0)
            {
                reset_game(&game);
                pellet_locations(&game);
                for (i = 0; i < 2; i++)
                    game.p_pellets[i].isEaten = 0;

                game.score_board.score = 0;
                game.score_board.life_count = 3;
            }

            /* Render everything */
			
            render(&game, base, cbase);
        }
    }

    return 0;
}
