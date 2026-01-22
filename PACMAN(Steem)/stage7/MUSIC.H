#ifndef MUSIC_H
#define MUSIC_H

#include "PSG.H"
#include "raster.h"

/* --- Constants --- */
#define WAKA_INTERVAL 100   /* milliseconds between tone flips */

extern const int A5_TONE;
extern const int G5_TONE;
extern int current_tone;

/*starts the music using chanel A*/
void start_music();

/*updates the music to what it shoud be for the givin time elapsed*/
void update_music(UINT32 time_elapsed);

void repair_psg();

#endif