#ifndef RENDERER_H
#define RENDERER_H

#include "MODEL.H"
#include "RASTER.H"
#include "BITMAPS.H"


void render(const Model *model, UINT16 *base, char *cbase);
void render_pacman(const Pacman *p, UINT16 *base);
void render_ghost(const Ghost *g, UINT16 *base);
void render_pellet(const Pellet *p, UINT16 *base);
void render_power_pellet(const Pellet *p, UINT16 *base);
void render_maze(char *base);
void render_score(int score, UINT16 *base);
void render_digit(int d, int row, int col, UINT16 *base);

#endif
