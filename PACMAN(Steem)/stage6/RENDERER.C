#include "RENDERER.H"
#include "raster.h"
#include "events.h"
#include "digits.h"
#include <osbind.h>

void render_pacman(const Pacman *p, UINT16 *base)
{
   
	plot_bitmap_16(base, p->y, p->x, pacman_bitmap, 16);
}

void render_ghost(const Ghost *g, UINT16 *base)
{
    
	plot_bitmap_16(base, g->y, g->x, ghost_bitmap, 16);
}

void render_pellet(const Pellet *p, UINT16 *base)
{
	
    if (!p->isEaten)
		
        plot_bitmap_16(base, ((p->y)+6), p->x, pellet_bitmap, 4);
}

void render_power_pellet(const Pellet *p, UINT16 *base)
{
	
    if (!p->isEaten)
		
        plot_bitmap_16(base, ((p->y)+4), p->x, big_pellet_bitmap, 8);
}


void plot_outer_walls(char *base) {
	/*top wall segment*/
    plot_line(base, 0, 0, 0, 240);
    plot_line(base, 15, 15, 15, 224);
    /*left wall segment*/
	plot_line(base, 0, 0, 112, 0);
    plot_line(base, 15, 15, 96, 15);
    /*right wall segment*/
	plot_line(base, 0, 240, 112, 240);
    plot_line(base, 15, 224, 96, 224);    
    /*bottom wall segment*/
	plot_line(base, 112, 0, 112, 240);
    plot_line(base, 96, 15, 96, 224);
}

void plot_edge_walls(char *base) {
    /*outer wall jetout 1*/
	plot_line(base, 79, 16, 79, 48);
    plot_line(base, 79, 47, 64, 47);
    plot_line(base, 64, 16, 64, 47);
    /*outer wall jetout 2*/
    plot_line(base, 79, 224, 79, 176);
    plot_line(base, 79, 176, 64, 176);
    plot_line(base, 64, 176, 64, 224);
    /*outer wall jetout 3*/
    plot_line(base, 15, 112, 48, 112);
    plot_line(base, 47, 112, 47, 127);
    plot_line(base, 16, 127, 48, 127);
}

void plot_inner_walls(char *base) {
	/*inner wall 1*/
	plot_line(base, 32, 32, 47, 32);
    plot_line(base, 47, 32, 47, 64);
    plot_line(base, 47, 64, 79, 64);
    plot_line(base, 79, 64, 79, 127);
    plot_line(base, 79, 127, 64, 127);
    plot_line(base, 64, 128, 64, 80);
    plot_line(base, 64, 79, 32, 79);
    plot_line(base, 32, 79, 32, 32);    
    
	/*inner wall 2*/
    plot_line(base, 32, 207, 47, 207);
    plot_line(base, 47, 207, 47, 160);
    plot_line(base, 47, 159, 79, 159);
    plot_line(base, 79, 160, 79, 144);
    plot_line(base, 79, 144, 32, 144);
    plot_line(base, 32, 144, 32, 208);
	
}

/* draw maze walls based on Stage 3 grid */
void render_maze(char *base) {
    plot_outer_walls(base);

    plot_edge_walls(base);

    plot_inner_walls(base);
}

void render_score(int score, UINT16 *base)
{
    int x = 16;       /* left position */
    int y = 128;       /* top of screen */
    int digit;

    /* Render hundreds, tens, ones */
	digit = (score / 10000) % 10;
    render_digit(digit, y, x, base);
    x += 16;
	
	digit = (score / 1000) % 10;
    render_digit(digit, y, x, base);
    x += 16;
	
    digit = (score / 100) % 10;
    render_digit(digit, y, x, base);
    x += 16;

    digit = (score / 10) % 10;
    render_digit(digit, y, x, base);
    x += 16;

    digit = score % 10;
    render_digit(digit, y, x, base);
}

void render_digit(int d, int row, int col, UINT16 *base)
{
    
    if (d == 0) {
		plot_bitmap_16(base, row, col, DIGIT_0, 8);
    }
	if (d == 1) {
		plot_bitmap_16(base, row, col, DIGIT_1, 8);
    }
	if (d == 2) {
		plot_bitmap_16(base, row, col, DIGIT_2, 8);
    }
	if (d == 3) {
		plot_bitmap_16(base, row, col, DIGIT_3, 8);
    }
	if (d == 4) {
		plot_bitmap_16(base, row, col, DIGIT_4, 8);
    }
	if (d == 5) {
		plot_bitmap_16(base, row, col, DIGIT_5, 8);
    }
	if (d == 6) {
		plot_bitmap_16(base, row, col, DIGIT_6, 8);
    }
	if (d == 7) {
		plot_bitmap_16(base, row, col, DIGIT_7, 8);
    }
	if (d == 8) {
		plot_bitmap_16(base, row, col, DIGIT_8, 8);
    }
	if (d == 9) {
		plot_bitmap_16(base, row, col, DIGIT_9, 8);
    }
}

void render(const Model *model, UINT16 *base, char *cbase)
{
     static int maze_drawn_c = 0;  /* remember if maze was drawn already */
    int i, y, z;

    
    /* Draw maze once, not every frame */
    if (maze_drawn_c < 2) {
        clear_screen(base);  /* clear once at start */
        render_maze(cbase);
        maze_drawn_c++;
    }
    
	
	
    /* --- Moving objects --- */
    render_pacman(&model->pacman, base);

    for (i = 0; i < 2; i++) {
		if (model->ghosts[i].cooldownTimer == 0) {
			render_ghost(&model->ghosts[i], base);
		}
    }

    for (y = 0; y < 42; y++) {
        render_pellet(&model->pellets[y], base);
    }

    for (z = 0; z < 2; z++) {
        render_power_pellet(&model->p_pellets[z], base);
    }
	
	render_score(model->score_board.score, base);
	for (i = 0; i < model->score_board.life_count; i++) {
		plot_bitmap_16(base, 128, 112 + (16 * i), pacman_bitmap, 16);
	}
}

void erase_render(const Model *model, UINT16 *base) {
	int i, y, z;
	
	for (i = 0; i < 20; i++) {
        erase_old_bitmap(320, 320, base);
    }
	
	/* erases old bitmaps */
    erase_old_bitmap(model->pacman.x, model->pacman.y, base);
    for (i = 0; i < 2; i++) {
        erase_old_bitmap(model->ghosts[i].x, model->ghosts[i].y, base);
    }

    for (y = 0; y < 42; y++) {
        erase_old_bitmap(model->pellets[y].x, model->pellets[y].y, base);
    }

    for (z = 0; z < 2; z++) {
        erase_old_bitmap(model->p_pellets[z].x, model->p_pellets[z].y, base);
    }
	
	for (i = 0; i < 5; i++) {
		erase_old_bitmap(16 + (16 * i), 128, base);
	}
	
	render_score(model->score_board.score, base);
	for (i = 0; i < 3; i++) {
		erase_old_bitmap(112 + (16 * i),128 , base);
	}
}




