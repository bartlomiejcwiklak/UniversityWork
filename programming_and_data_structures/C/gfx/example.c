#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "gfx.h"
// cc test_fill_circle.c gfx.c -o test_fill_circle -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -lm

#define ysize 600
#define xsize 600
#define Xsize xsize / 2        
#define Ysize ysize / 2        // 300
#define A ysize / 60           // 10
#define B ysize - (ysize / 60) // 590
#define D ysize / 60           
#define C ysize - (ysize / 60) 
#define N xsize / 10           

void info(void)
{
#define couleur(param) printf("\033[%sm", param)
    couleur("32");
    couleur("0");
}

void cell_division(int n) 
{
    for (int i = 0; i <= C; i = (i + n)) 
    {
        gfx_line(A + i, D, A + i, C); 
        gfx_line(A, D + i, B, D + i); 
    }
}

int main()
{
    info();
    gfx_open(xsize, ysize, "huj");

    gfx_color(30, 30, 30);
    cell_division(A);
    gfx_color(0, 0, 255); 

    gfx_color(255, 0, 0); 
    gfx_circle(Xsize, Ysize, 200, 200);
    gfx_point(100, 100);

    gfx_color(0, 0, 255); 
    gfx_fill_circle(100, 100, 100, 100);
    gfx_point(Xsize, Ysize); 

    gfx_wait();
    return 0;
}