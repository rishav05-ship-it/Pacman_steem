#include "music.h"
#include "psg.h"

/* Music alternates between A5 and G5 on channel 0 (tone A) */

const int A5_TONE = 142;
const int G5_TONE = 160;

static int music_playing = 0;
int current_tone = 0;                 /* 0 = A5, 1 = G5 */
static UINT32 time_accumulator = 0;   /* ms since last toggle */

#define WAKA_INTERVAL 120    /* ms per “waka” sound */


/* Start looping tone-based music */
void start_music()
{
    stop_sound();    /* clear PSG */

    current_tone = 0;
    time_accumulator = 0;
    music_playing = 1;

    /* Tone A: A5 */
    set_tone(0, A5_TONE);
	
	write_psg(7, 0x2C);

    /* Enable tone A only (mixer handled elsewere) */
    /* Volume will be restored in repair window */
    set_volume(0, 12);
}


/* Update music, toggles tone A <-> G */
void update_music(UINT32 delta_ms)
{
    if (!music_playing) return;

    time_accumulator += delta_ms;

    if (time_accumulator >= WAKA_INTERVAL)
    {
        time_accumulator = 0;

        if (current_tone == 0) {
            set_tone(0, G5_TONE);
            current_tone = 1;
        } else {
            set_tone(0, A5_TONE);
            current_tone = 0;
        }
    }
}

void repair_psg()
{
    /* Read mixer, enable tone A only (clear bit 0) but leave all other bits alone.
      This avoids disabling noise or touching channel B at all. */
    UINT8 m = (UINT8) read_psg(7);
	
	/* Restore tone A to the current tone so phase is correct */
    if (current_tone == 0)
        set_tone(0, A5_TONE);
    else
        set_tone(0, G5_TONE);

    write_psg(7, 0x2C);

    /* Restore only music volume (channel A). Do NOT write channel B volume here. */
    set_volume(0, 12);
}