#include "raster.h"
#include "bitmaps.h"
#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include <stdlib.h>


int raster_test() {
    char *base = Physbase();
    UINT16 *lbase = Physbase(); 
    	
    clear_screen(lbase);

    plot_pixel(base, 5, 5);

    plot_hline(base, 50, 590, 350);
    
    plot_vline(base, 590, 50, 350);
    
	
    plot_bitmap_16(lbase, 50, 50, pacman_bitmap, 16);

    
    plot_bitmap_16(lbase, 70, 50, ghost_bitmap, 16);
    
    
    plot_bitmap_16(lbase, 90, 50, pellet_bitmap, 4);

   
    plot_bitmap_16(lbase, 110, 50, big_pellet_bitmap, 8);

    return 0;
}


void clear_screen(UINT16 *base)
{
    int i = 0;
    while (i < FRAMEBUFFER_SIZE) {

		base[i] = 0x0000;
	        i++;
    }
}




void plot_pixel(char *base, int row, int col)
{
    if (col >= 0 && col < SCREEN_WIDTH && row >= 0 && row < SCREEN_HEIGHT)
    {
        *((base + (row*80)) + (col >> 3)) |= (1 << (7 - (col & 7)));
    }
}


void plot_hline(char *base, int row, int x1, int x2)
 {
    int i;
    if (row < 0 || row >= SCREEN_HEIGHT)
        return;


   
    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }


    /* draw the horizontal line */
    i = x1;
    while (i <= x2) {
        plot_pixel(base, row, i);
        i++;
    }
}




void plot_vline(char *base, int col, int y1, int y2){
    int y;
    if (col < 0 || col >= SCREEN_WIDTH)
        return;


   
    if (y1 > y2)
    {
        int temp = y1;
        y1 = y2;
        y2 = temp;
    }


    /* draw the vertical line*/
    y = y1;
    while (y <= y2)
    {
        plot_pixel(base, y, col);
        y++;
    }
}


void plot_line(char *base, int x1, int y1, int x2, int y2) {
    int line_plot = abs(x2 - x1);  
    int line_plot2 = abs(y2 - y1);  
    int sx, sy;            
    int tracking;
    int error_term;

    if (x1 < x2)
        sx = 1;
    else
        sx = -1;


    if (y1 < y2)
        sy = 1;
    else
        sy = -1;


    tracking = line_plot - line_plot2;      

    /* their are break's in the code */
    while (1)
    {
        plot_pixel(base, x1, y1);  


        if (x1 == x2 && y1 == y2)
            break;                  


        error_term = 2 * tracking;          


        if (error_term > -line_plot2)
        {            
            tracking -= line_plot2;
            x1 += sx;
        }


        if (error_term < -line_plot)
        {              
            tracking += line_plot;
            y1 += sy;
        }
    }
}


/**/
void plot_bitmap_16(UINT16 *base, int row, int col, const UINT16 *bitmap, 
	int height) {
    int x_long, y_offset, i;
    x_long = col >> 4;

    i = 0;
    while (i < height) {
        y_offset = (row + i) * SCREEN_WIDTH_L;
        base[y_offset + x_long] |= bitmap[i];
        i++;
    }
}

void erase_old_bitmap(int col, int row, UINT16 *base) {
	int x_long, y_offset, i, height;
	height = 16;
    x_long = col >> 4;

    i = 0;
    while (i < height) {
        y_offset = (row + i) * SCREEN_WIDTH_L;
        base[y_offset + x_long] = empty[i];
        i++;
    }
	
}





