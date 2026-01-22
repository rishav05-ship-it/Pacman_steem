#include "model.h"

#ifndef EVENTS_H
#define EVENTS_H


/*takes in a key and if it is w,a,s, or d 
sets pacmans velocity in that direction.*/

void move_request(Pacman *p, char key);


/**/

void ghost_collide(Ghost *g, Score_board *s);/*look at later*/


/**/

void lose_life(Score_board *s);


void pacman_clock(Ghost *g1, Ghost *g2);


int check_collision(Pacman *p, Ghost *g);

int check_game_over(Score_board *s);

int check_exit_request(int key);

/*returns 1 if the player has zero lives remaining an 0 otherwise*/
int end_game_check(Score_board *s);

void scared_ghost_move(Ghost *g);

void update_ghost(Ghost *g, Pacman *p);

#endif
