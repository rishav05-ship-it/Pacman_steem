#ifndef RASTER_H
#define RASTER_H


#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH_L 40
#define FRAMEBUFFER_SIZE 16000   /* 640*400 / 16*/

typedef unsigned char UINT8;

typedef unsigned int UINT16;

typedef unsigned long UINT32;


void clear_screen(UINT16 *base);


void plot_pixel(char *base, int row, int col);


void plot_hline(char *base, int row, int x1, int x2);


void plot_vline(char *base, int col, int y1, int y2);


void plot_line(char *base, int x1, int y1, int x2, int y2);


void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap, int height);
	 

void erase_old_bitmap(int col, int row, UINT16 *base);







#endif
