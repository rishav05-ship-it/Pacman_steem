#include <osbind.h>
#include "RENDERER.C"


void pellet_locations(Model *game);

int main(void)
{
    UINT16 *base;
    char *cbase;
    Model game;
    int i;

    base = Physbase();
    cbase = Physbase();

    /* Pac-Man start position (in an open tile) */
    game.pacman.x = 16;
    game.pacman.y = 16;
    game.pacman.dx = 0;
    game.pacman.dy = 0;

    /* two ghosts */
    for (i = 0; i < 2; i++)
    {
        game.ghosts[i].x = 80 + (i * 16);
        game.ghosts[i].y = 80;
    }

    /* pellets */
    
    pellet_locations(&game);
    


    /* power pellets */
    for (i = 0; i < 2; i++)
    {
        game.p_pellets[i].x = 16 + (i * (16*12));
        game.p_pellets[i].y = 80;
        game.p_pellets[i].isEaten = 0;
        game.p_pellets[i].isPower = 1;
    }

    /* draw full frame: maze + objects */
    render(&game, base, cbase);

    Cnecin();    /* wait for key before exit */
    return 0;
}

void pellet_set(Pellet *p, int x1, int y1) {
	p->x = x1;
    p->y = y1;
	p->points = 200;
    p->isEaten = 0;
    p->isPower = 0;
}

void pellet_locations(Model *game) {
    int i = 0;
	int y = 0;
    for (y = 0; y < 6; y++) {
        pellet_set(&game->pellets[i], (16+(y *16)), 16);
        i++;
    }
	for (y = 0; y < 6; y++) {
        pellet_set(&game->pellets[i], (128+(y *16)), 16);
        i++;
    }
	pellet_set(&game->pellets[i], 16, 32);
	i++;
	pellet_set(&game->pellets[i], 80, 32);
	i++;
	pellet_set(&game->pellets[i], 96, 32);
	i++;
	pellet_set(&game->pellets[i], 128, 32);
	i++;
	pellet_set(&game->pellets[i], 208, 32);
	i++;
	for (y = 0; y < 3; y++) {
		pellet_set(&game->pellets[i], (16 +(y*16)), 48);
	    i++;
	}
	for (y = 0; y < 4; y++) {
		pellet_set(&game->pellets[i], (80 +(y*16)), 48);
	    i++;
	}
	for (y = 0; y < 4; y++) {
		pellet_set(&game->pellets[i], (160 +(y*16)), 48);
	    i++;
	}
	pellet_set(&game->pellets[i], 48, 64);
	i++;
	pellet_set(&game->pellets[i], 128, 64);
	i++;
	pellet_set(&game->pellets[i], 160, 64);
	i++;
	for (y = 0; y < 11; y++) {
		pellet_set(&game->pellets[i], (32 +(y*16)), 80);
	    i++;
	}
	
}

