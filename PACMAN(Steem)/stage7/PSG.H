#ifndef PSG_H
#define PSG_H
#include "RASTER.H"

#define SELECT	0xFF8800
#define WRITE	0xFF8802



/* registers number key.
 0  - A fine tone adjustment (8 bit)
 1  - A rough tone adjustment (4 bit)
 2  - B fine tone adjustment (8 bit)
 3  - B rough tone adjustment (4 bit)
 4  - C fine tone adjustment (8 bit)
 5  - C rough tone adjustment (4 bit)
 6  - noise frequency (5 bit)
 7  - I/O port and mixer settings (8 bit)
 8  - level of channel A (5 bit)
 9  - level of channel B (5 bit)
 10 - level of channel C (5 bit)
 11 - frequency of envelope fine adjustment (8 bit)
 12 - frequency of envelope rough adjustment (8 bit)
 13 - shape of envelope (4 bit , CONT, ATT, ALT, HOLD)
 14 - data of I/O port A (8 bit)
 15 - data of I/O port B (8 bit)
*/

/*writes a byte value(0-255) to one of the PSG registers(0-15)*/
void write_psg(int reg, UINT8 val);

/*reads the value in a givin register and returns it*/
int read_psg(int reg);

/*sets the chosen chanel A(0), B(1), or C(2) to a 12 bit tuning value that
 is seperated into rough and fine*/
void set_tone(int channel, int tuning);

/*opens the volume register for the givin channel*/
void set_volume(int channel, int volume);

/*turns a given channels tone and noise signals on or off off(0) and on(1)*/
void enable_channel(int channel, int tone_on, int noise_on);

/*stops all sound by setting the volume channel to 0*/
void stop_sound();

/*sets the noise value to the givin tuning*/
void set_noise(int tuning);

/*sets the envelope to the givin shape(4 bit) and
 puts the sustain(16 bit) into the rough(8 bit) and fine(8 bit) adqustments*/
void set_envelope(int shape, unsigned int sustain);

#endif