#ifndef MODEL_H
#define MODEL_H

#define ROWS 7
#define COLS 15
#define TILE_SIZE 16

typedef struct 
{
    int x, y;        
    int dx, dy;        
} Pacman;


typedef struct 
{
    int x, y;        
    int dx, dy;      
    int isScared;       
    int cooldownTimer;  
    int points;        

} Ghost;                        


typedef struct 
{
    int x, y;
    int isEaten;   
    int points;    
    int isPower;   

} Pellet;                       
                          

typedef struct
{
    int x1, y1;    
    int x2, y2;  

} Wall;                                 


typedef struct 
{
    unsigned int score;
    int life_count;
} Score_board;

#define MAX_GHOSTS   2
#define MAX_PELLETS  200
#define POWER_PELS   4
#define MAX_WALLS    100



typedef struct
{
    Pacman pacman;
    Ghost ghosts[MAX_GHOSTS];
    Pellet p_pellets[POWER_PELS];
    Pellet pellets[MAX_PELLETS];
    Wall walls[MAX_WALLS];
    Score_board score_board;

} Model;

extern int maze[ROWS][COLS];


int wall_collision(Pacman *p);

/*takes pacmans velocity and adds it to his position.
then sets his x and y velocity to zero.*/

void move_pacman(Pacman *p);


/*resets pacmans position to the x and y given 
and sets his velocities to zero.*/

void reset_pacman(Pacman *p, int x, int y);


void move_ghost(Ghost *g);

void reset_ghost(Ghost *g, int x, int y);

void reset_game(Model *game);

void eat_ghost(Ghost *g, Score_board *s);


void eat_pellet(Pellet *pellet, Score_board *s, Ghost *g1, Ghost *g2);

int all_pellets_eaten(Model *game);


#endif                       
