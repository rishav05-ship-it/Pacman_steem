#include <osbind.h>
#include <string.h>
#include "POS_STA.H"
#include "model.h"
#include "events.h"
#include "renderer.h"
#include "effects.h"
#include "music.h"


/*for tests delete later*/
#include <stdio.h>

#define TICK_ADDRESS 0x462

/* ---------------------------------------------------------
   Read 70 Hz timer
--------------------------------------------------------- */
unsigned long get_time()
{
    unsigned long old = Super(0);
    unsigned long t = *(volatile unsigned long *)TICK_ADDRESS;
    Super(old);
    return t;
}

/* ---------------------------------------------------------
   Wait for Vertical Blank
--------------------------------------------------------- */


void wait_vblank()
{
    long old = Super(0);
	volatile UINT32 *vblank_c = (volatile UINT32 *)0x462;
    UINT32 last = *vblank_c;

    /* Wait until the counter increments */
    while (*vblank_c == last)
    {
        /* spin*/
    }
	Super(old);
}


/* =========================================================
   MAIN — FINAL WORKING STAGE 6 DOUBLE BUFFERING
========================================================= */
int main()
{
    UINT8  *mem;
    UINT16 *front;   /* shown on screen */
    UINT16 *back;    /* draw here */
    UINT16 *tmp;

    UINT16 *original = Physbase(); /* restore at end */
	
	/*for update music*/
	unsigned long ticks_delta;
	unsigned long ms_delta;

    unsigned long prev, curr;
    int i, key = 0;
	int ghost_interval = 0;
    Model game;
	
	int restore_frames = 0;
	

    /* ---------------------------------------------------------
       Allocate TWO BUFFERS (32000 bytes each + alignment)
    --------------------------------------------------------- */
    mem = (UINT8 *)Malloc(64000 + 512);
    if (!mem) return 0;

    /* front buffer aligned */
    front = (UINT16*)(((long)mem + 255) & ~255);

    /* back buffer aligned 32000 bytes later */
    back = (UINT16*)(((long)front + 32000 + 255) & ~255);

    /* ---------------------------------------------------------
       Stage 5 setup (unchanged)
    --------------------------------------------------------- */
    game.pacman.x = 112;
    game.pacman.y = 48;
    game.pacman.dx = 0;
    game.pacman.dy = 0;

    game.ghosts[0].x = 48;
    game.ghosts[0].y = 48;
    game.ghosts[0].dx = 1;
    game.ghosts[0].dy = 0;
    game.ghosts[0].isScared = 0;
    game.ghosts[0].cooldownTimer = 0;
    game.ghosts[0].points = 200;

    game.ghosts[1].x = 192;
    game.ghosts[1].y = 48;
    game.ghosts[1].dx = -1;
    game.ghosts[1].dy = 0;
    game.ghosts[1].isScared = 0;
    game.ghosts[1].cooldownTimer = 0;
    game.ghosts[1].points = 20;

    pellet_locations(&game);

    for (i = 0; i < 2; i++) {
        game.p_pellets[i].x = 16 + (i * (16 * 12));
        game.p_pellets[i].y = 80;
        game.p_pellets[i].isEaten = 0;
        game.p_pellets[i].isPower = 1;
        game.p_pellets[i].points = 5;
    }

    game.score_board.score = 0;
    game.score_board.life_count = 3;

    /* ---------------------------------------------------------
       INITIAL DRAW INTO FRONT BUFFER
    --------------------------------------------------------- */
    memset(front, 0, 32000);
    render(&game, front, (char*)front);

    Setscreen(-1, front, -1);	
	
    prev = get_time();
	
	/*start music*/
	start_music();

    /* =========================================================
       MAIN LOOP — TRUE DOUBLE BUFFERING
    ========================================================= */
    while (!check_exit_request(key))
    {
        /* keyboard */
        if (Cconis()) {		
			key = Cnecin();
			
			restore_frames = 2;
			
            move_request(&game.pacman, key);

        }

        curr = get_time();
        if (curr != prev)
        {
            
			ticks_delta = curr - prev; /* number of 70Hz ticks elapsed */
			ms_delta = (ticks_delta * 1000) / 70; /*convert to ms*/
			
			prev = curr;
			
			/* repares because pressing a key stops sounds */
            if (restore_frames > 0) {
                repair_psg();
                restore_frames--;
            }
            
            move_pacman(&game.pacman);

            for (i = 0; i < 42; i++) {
                if (game.pacman.x == game.pellets[i].x &&
                    game.pacman.y == game.pellets[i].y) {
                    eat_pellet(&game.pellets[i], &game.score_board,
                               &game.ghosts[0], &game.ghosts[1]);
				}
			}

            for (i = 0; i < 2; i++) {
                if (game.pacman.x == game.p_pellets[i].x &&
                    game.pacman.y == game.p_pellets[i].y) {
					if (game.p_pellets[i].isEaten == 0) {
						play_eat_power();
					}
					eat_pellet(&game.p_pellets[i], &game.score_board,
                               &game.ghosts[0], &game.ghosts[1]);
				}
		    }

            for (i = 0; i < 2; i++)
            {
				if (ghost_interval % 10 == 0)
                {
					if (game.ghosts[i].cooldownTimer == 0)
					{
						if (!game.ghosts[i].isScared) {
							update_ghost(&game.ghosts[i], &game.pacman); }
						else if (ghost_interval % 20 == 0) {
							update_ghost(&game.ghosts[i], &game.pacman); }
					}
                }
		    }
			ghost_interval++;
            

            for (i = 0; i < 2; i++)
            {
                if (check_collision(&game.pacman, &game.ghosts[i]))
                {
                    if (!game.ghosts[i].isScared && !game.ghosts[i].cooldownTimer)
                    {
                        lose_life(&game.score_board);
						play_death();
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
                for (i = 0; i < 2; i++) game.p_pellets[i].isEaten = 0;
            }

            if (game.score_board.life_count == 0)
            {
                reset_game(&game);
                pellet_locations(&game);
                for (i = 0; i < 2; i++) game.p_pellets[i].isEaten = 0;

                game.score_board.score = 0;
                game.score_board.life_count = 3;
            }

            /* =================================================
               1. CLEAR BACK BUFFER + RENDER EVERYTHING
            ================================================= */
            /*memset(back, 0, 32000);*/
            render(&game, back, (char*)back);

            /* =================================================
               2. WAIT FOR VBLANK
            ================================================= */
            wait_vblank();

            /* =================================================
               3. FLIP: SHOW BACK BUFFER ON THE SCREEN
            ================================================= */
            
			/*stoping somewhere before here*/
			Setscreen(-1, back, -1);

            /* =================================================
               4. SWAP POINTERS (BACK ↔ FRONT)
            ================================================= */
            tmp = front;
            front = back;
            back = tmp;
			
			erase_render(&game, back);
			
			update_music(ms_delta);
        }
    }

    /* stop sound */
    stop_sound();

    /* restore */
    Setscreen(-1, original, -1);
    Mfree(mem);

    return 0;
}