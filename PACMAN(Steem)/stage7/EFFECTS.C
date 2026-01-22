#include "EFFECTS.H"

#include "MUSIC.H"


/* Plays the full death sound: sets tone, noise, mixer, 
   volume, and envelope on Channel B */
   
void play_death() {
	set_tone(1, 0x537);
	set_noise(1);
	write_psg(7, 0x2C);	
	set_volume(1, 16);
	set_envelope(0x00, 0x1035);
}

/* Plays the full power-pellet sound: 
sets tone, noise, mixer, volume, and envelope on Channel B */

void play_eat_power() {
    set_tone(1, 0x250);
    set_noise(1);
    write_psg(7, 0x2C);   
    set_volume(1, 16);
    set_envelope(0x09, 0x1400);
}
