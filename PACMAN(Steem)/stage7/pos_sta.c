#include "RENDERER.H"

void pellet_set(Pellet *p, int x1, int y1) {
	p->x = x1;
    p->y = y1;
	p->points = 1;
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