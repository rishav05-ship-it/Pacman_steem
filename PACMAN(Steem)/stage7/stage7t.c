#include "EFFECTS.C"
#include "PSG.c"
#include <osbind.h>

int main() {
	
    write_psg(7, 0x38);
	play_eat_power();
    
	while(!Cconis()) {
    }
	
	stop_sound();

	Cnecin();
}