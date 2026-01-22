#include "model.h"


int maze[ROWS][COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,0,1,0,1,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
    {1,1,1,0,1,1,1,1,0,1,0,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


int wall_collision(Pacman *p) {
	int next_x_1 = p->x + p->dx;
    int next_y_1 = p->y + p->dy;
	
	int next_x_2 = p->x + p->dx + 15;
	int next_y_2 = p->y + p->dy + 15;

    int col_1 = next_x_1 / TILE_SIZE;
    int row_1 = next_y_1 / TILE_SIZE;
	
	int col_2 = next_x_2 / TILE_SIZE;
    int row_2 = next_y_2 / TILE_SIZE;

    /* Out of bounds = wall */
    if (row_1 < 0 ||  row_1 >= ROWS || col_1 < 0 || col_1 >= COLS)
        return 1;
	
	if (row_2 < 0 ||  row_2 >= ROWS || col_2 < 0 || col_2 >= COLS)
        return 1;

    /* 1 means wall */
    return (maze[row_1][col_1] == 1 || maze[row_1][col_2] == 1 
	      || maze[row_2][col_1] == 1 || maze[row_2][col_2] == 1);
}

void move_pacman(Pacman *p) {
    if(!wall_collision(p)){
        p->x += p->dx;        
        p->y += p->dy;               
    }
	
    p->dx = 0;
    p->dy = 0;
}

void reset_pacman(Pacman *p, int x, int y) {
    p->x = x;  
    p->y = y;
    p->dx = 0;   
    p->dy = 0;
}

void move_ghost(Ghost *g) {
    g->x += g->dx;
    g->y += g->dy;

    g->dx = 0;
    g->dy = 0;
}


void reset_ghost(Ghost *g, int x, int y)
{
    g->x = x;
    g->y = y;
    g->dx = 0;
    g->dy = 0;
    g->isScared = 0;
    g->cooldownTimer = 0;
}

void reset_game(Model *game)
{
    reset_pacman(&game->pacman, 112, 48);

    reset_ghost(&game->ghosts[0], 48, 48);

    reset_ghost(&game->ghosts[1], 192, 48);
}


void eat_ghost(Ghost *g, Score_board *s) 
{
    s->score += g->points;

    g->cooldownTimer = 70;   

    g->isScared = 0;          
}


void eat_pellet(Pellet *pellet, Score_board *s, Ghost *g1, Ghost *g2) 
{
    if (pellet->isEaten == 0)
     {
        pellet->isEaten = 1;
        s->score += pellet->points;

        if (pellet->isPower) 
        {
            g1->isScared = 100;
            g2->isScared = 100; 
        }
    }
}

int all_pellets_eaten(Model *game)
{
    int i;

    /* regular pellets */
    for (i = 0; i < 42; i++)
    {
        if (game->pellets[i].isEaten == 0)
            return 0;   /* at least one pellet not eaten */
    }

    /* power pellets */
    for (i = 0; i < 2; i++)
    {
        if (game->p_pellets[i].isEaten == 0)
            return 0;
    }

    return 1;  /* ALL pellets eaten */
}
