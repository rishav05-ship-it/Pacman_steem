#include "PSG.H"
#include <osbind.h> /*for Super()*/

/*writes a byte value(0-255) to one of the PSG registers(0-15)*/
void write_psg(int reg, UINT8 val) {
    volatile char *PSG_reg_select = SELECT;
	volatile char *PSG_reg_write = WRITE;
	long old_ssp;
	
	/*returns if a value is outside of range*/
	if (reg < 0 || reg > 15 || val < 0 || val > 255) {
		return;
	}
	
	old_ssp = Super(0);
	
	*PSG_reg_select = reg;
	*PSG_reg_write = val;
	
	Super(old_ssp);
	return;
}

/*reads the value in a givin register and returns it*/
int read_psg(int reg) {
	volatile char *PSG_reg_select = SELECT;
	volatile char *PSG_reg_write = WRITE;
	long old_ssp;
	
	int held_val;
	
	if (reg < 0 || reg > 15) {
		return -1; /*returns outside of range*/
	}
	
	old_ssp = Super(0);
	
	*PSG_reg_select = reg;
	held_val = *PSG_reg_write;
	
	Super(old_ssp);
	return held_val;
}

/*sets the chosen chanel A(0), B(1), or C(2) to a 12 bit tuning value that
 is seperated into rough and fine*/
void set_tone(int channel, int tuning) {
    UINT8 fine;
    UINT8 rough;

    if (channel > 2 || channel < 0 || tuning > 4095 || tuning < 0) {
        return;
    }

    fine  = (UINT8)(tuning & 0xFF);
    rough = (UINT8)((tuning >> 8) & 0x0F);

    write_psg((channel * 2), fine);
    write_psg((channel * 2) + 1, rough);
}

/*loads the volume register for the givin channel A(0), B(1), and C(2)
 with the givin volume*/
void set_volume(int channel, int volume) {
	UINT8 u_vol;
	if (channel > 2 || channel < 0 || volume > 32 || volume < 0) {
		return; /*returns if parameters were outside of range*/
	}
	u_vol = volume;
	
	write_psg((channel + 8), u_vol);
}

/*turns a given channels A(0), B(1), and C(2) tone and noise 
 signals on or off off(0) and on(1)*/
void enable_channel(int channel, int tone_on, int noise_on) {
	UINT8 channel_gates = read_psg(7);
	if (channel > 2 || channel < 0) {
		return; 
	}
	if (tone_on > 1 || tone_on < 0 || noise_on > 1 || noise_on < 0) {
		return; 
	}
	/*AI consulted to help understand how to set and unset one bit*/
	if (tone_on == 1) {
		channel_gates &= ~(1 << channel);
	} else {
		channel_gates |= (1 << channel);
	}
	
	if (noise_on == 1) {
		channel_gates &= ~(1 << (channel + 3));
	} else {
		channel_gates |= (1 << (channel + 3));
	}
	/*help ends here*/
	
	write_psg(7, channel_gates);
}

/*stops all sound by setting the volume channel to 0*/
void stop_sound() {
	
	write_psg(7, 0x3F); /*sets I/O port to 0 and mixer to 1 to stop sound*/
	
	write_psg(8, 0); /*sets channel A level to 0*/
	write_psg(9, 0); /*sets channel B level to 0*/
	write_psg(10, 0); /*sets channel C level to 0*/
}

/*sets the noise value to the givin tuning*/
void set_noise(int tuning) {
	UINT8 u_tun = tuning;
	write_psg(6, tuning);
}

/*sets the envelope to the givin shape(4 bit) and
 puts the sustain(16 bit) into the rough(8 bit) and fine(8 bit) adqustments*/
void set_envelope(int shape, unsigned int sustain) {
	UINT8 u_shape = shape;
	UINT8 u_fine = sustain;
	UINT8 u_rough = sustain >> 8;
	
	write_psg(11, u_fine); /*sets fine*/
	
	write_psg(12, u_rough); /*sets rough*/
	
	write_psg(13, u_shape); /*sets shape*/
}