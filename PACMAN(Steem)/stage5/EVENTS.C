#include "events.h"
#include "model.h"

/* ========================= */
/*      PLAYER CONTROLS      */
/* ========================= */

void move_request(Pacman *p, char key) {
    if (key == 'w')  p->dy = -16;
    if (key == 's')  p->dy =  16;
    if (key == 'a')  p->dx = -16;
    if (key == 'd')  p->dx =  16;
}


/* ========================= */
/*      COLLISION LOGIC      */
/* ========================= */

void ghost_collide(Ghost *g, Score_board *s) {
    if (g->cooldownTimer > 0)
        return;

    if (g->isScared > 0) {
        eat_ghost(g, s);
        return;
    }

    lose_life(s);
}

void pacman_clock(Ghost *g1, Ghost *g2) {
    if (g1->isScared > 0) g1->isScared -= 1;
    if (g1->cooldownTimer > 0) g1->cooldownTimer -= 1;
    if (g2->isScared > 0) g2->isScared -= 1;
    if (g2->cooldownTimer > 0) g2->cooldownTimer -= 1;
}

void lose_life(Score_board *s) {
    if (s->life_count > 0) {
        s->life_count--;
	}
}

int check_collision(Pacman *p, Ghost *g) {
    return (p->x == g->x && p->y == g->y);
}

int check_game_over(Score_board *s) {
    return (s->life_count <= 0);
}

int check_exit_request(int key) {
    return (key == 0x01 || key == 0x1B);
}

int end_game_check(Score_board *s) {
    return (s->life_count <= 0);
}


/* ========================= */
/*     SCARED GHOST MOVE     */
/* ========================= */


void scared_ghost_move(Ghost *g)
{
    /* 4 possible directions (left, right, up, down) */
    int dirs[4][2] = {
        {-1,0},  /* left  */
        { 1,0},  /* right */
        { 0,-1}, /* up    */
        { 0, 1}  /* down  */
    };

    int i;

    /* Get the ghost's current tile */
    int gx = g->x / TILE_SIZE;
    int gy = g->y / TILE_SIZE;

    for (i = 0; i < 4; i++)
    {
        /* Next tile in this direction */
        int tx = gx + dirs[i][0];
        int ty = gy + dirs[i][1];

        /* Check tile is inside maze & walkable */
        if (tx >= 0 && tx < COLS &&
            ty >= 0 && ty < ROWS &&
            maze[ty][tx] == 0)
        {
            /* Move 1 full tile (16 pixels) */
            g->dx = dirs[i][0] * TILE_SIZE;
            g->dy = dirs[i][1] * TILE_SIZE;

            move_ghost(g);
            return;
        }
    }

    /* If no direction works, stop ghost */
    g->dx = 0;
    g->dy = 0;
}



/* ========================= */
/*      BFS PATHFINDING      */
/* ========================= */

#define MAX_NODES 1000

typedef struct {
    int x;
    int y;
} Node;

/* Arrays used in BFS */
int bfs_parent[ROWS][COLS][2];
int visited[ROWS][COLS];

int bfs_dirs[4][2] = {
    {-1, 0},
    { 1, 0},
    { 0,-1},
    { 0, 1}
};


/* BFS Search */
int bfs_find_path(int sx, int sy, int tx, int ty)
{
    Node queue[MAX_NODES];
    int front = 0;
    int back = 0;
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++) {
            visited[i][j] = 0;
            bfs_parent[i][j][0] = -1;
            bfs_parent[i][j][1] = -1;
        }

    queue[back].x = sx;
    queue[back].y = sy;
    back++;

    visited[sy][sx] = 1;

    while (front < back)
    {
        Node cur = queue[front];
        front++;

        if (cur.x == tx && cur.y == ty)
            return 1;

        for (i = 0; i < 4; i++)
        {
            int nx = cur.x + bfs_dirs[i][0];
            int ny = cur.y + bfs_dirs[i][1];
			
			int nx2 = (((cur.x * TILE_SIZE) + 15) / TILE_SIZE) + bfs_dirs[i][0];
            int ny2 = (((cur.y * TILE_SIZE) + 15) / TILE_SIZE) + bfs_dirs[i][1];

            if (maze[ny][nx] == 0 && maze[ny2][nx] == 0 && maze[ny][nx2] == 0 &&
                maze[ny2][nx2] == 0 && !visited[ny][nx])
            {
                visited[ny][nx] = 1;
                bfs_parent[ny][nx][0] = cur.x;
                bfs_parent[ny][nx][1] = cur.y;

                queue[back].x = nx;
                queue[back].y = ny;
                back++;
            }
        }
    }

    return 0;
}


/* Get next step based on BFS */
void bfs_next_step(int sx, int sy, int tx, int ty, int *dx, int *dy)
{
    int cx, cy, px, py;

    if (!bfs_find_path(sx, sy, tx, ty)) {
        *dx = 0;
        *dy = 0;
        return;
    }

    cx = tx;
    cy = ty;

    px = bfs_parent[cy][cx][0];
    py = bfs_parent[cy][cx][1];

    while (!(px == sx && py == sy))
    {
        cx = px;
        cy = py;

        px = bfs_parent[cy][cx][0];
        py = bfs_parent[cy][cx][1];
    }

    *dx = (cx - sx) * 16;
    *dy = (cy - sy) * 16;
}


/* ========================= */
/*        UPDATE GHOST       */
/* ========================= */

void update_ghost(Ghost *g, Pacman *p)
{
    int gx = g->x / TILE_SIZE;
    int gy = g->y / TILE_SIZE;

    int px = p->x / TILE_SIZE;
    int py = p->y / TILE_SIZE;

    int dx, dy;

    if (g->isScared > 0) {
        scared_ghost_move(g);
        return;
    }

    bfs_next_step(gx, gy, px, py, &dx, &dy);

    g->dx = dx;
    g->dy = dy;

    move_ghost(g);
}




