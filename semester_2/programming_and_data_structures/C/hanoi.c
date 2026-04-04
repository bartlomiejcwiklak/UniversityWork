#include "primlib.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_DISKS 3
#define NUM_PEGS 3

typedef struct {
    int size;
    int peg;
} Disk;

Disk disks[NUM_DISKS];
int pegs[NUM_PEGS][NUM_DISKS];
int peg_top[NUM_PEGS] = {-1, -1, NUM_DISKS - 1};
int selected_disk = 0;

void draw_hanoi() {
    gfx_filledRect(0, 0, 1280, 720, BLACK);
    int window_width = 1280;
    int window_height = 720;
    int base_width = 700;
    int base_height = 20;
    int peg_height = 200;
    int peg_width = 20;
    int disk_height = 20;
    int game_height = peg_height + base_height;
    int offset_x = (window_width - base_width) / 2;
    int offset_y = (window_height - game_height) / 2;
    int base_y = offset_y + peg_height;
    
    gfx_filledRect(offset_x, base_y, offset_x + base_width, base_y + base_height, WHITE);
    
    for (int i = 0; i < NUM_PEGS; i++) {
        int peg_center = offset_x + (i + 1) * (base_width / 4);
        int peg_left = peg_center - peg_width / 2;
        int peg_right = peg_center + peg_width / 2;
        gfx_filledRect(peg_left, offset_y, peg_right, offset_y + peg_height, WHITE);
    }
    
    for (int i = 0; i < NUM_DISKS; i++) {
        int peg = disks[i].peg;
        int level = -1;
        
        for (int j = 0; j <= peg_top[peg]; j++) {
            if (pegs[peg][j] == i) {
                level = j;
                break;
            }
        }
        
        if (level == -1) continue;
        int disk_width = disks[i].size * 20;
        int peg_center = offset_x + (peg + 1) * (base_width / 4);
        int disk_x = peg_center - disk_width / 2;
        int peg_bottom_y = offset_y + peg_height;
        int disk_y = peg_bottom_y - (level + 1) * disk_height;
        enum color disk_color = (i == selected_disk) ? BLUE : RED;
        gfx_filledRect(disk_x, disk_y, disk_x + disk_width, disk_y + disk_height, disk_color);
    }
    gfx_updateScreen();
}

void move_disk(int new_peg) {
    int current_peg = disks[selected_disk].peg;
    if (peg_top[current_peg] >= 0 && pegs[current_peg][peg_top[current_peg]] == selected_disk) {
        if (peg_top[new_peg] == -1 || disks[selected_disk].size < disks[pegs[new_peg][peg_top[new_peg]]].size) {
            pegs[current_peg][peg_top[current_peg]--] = -1;
            pegs[new_peg][++peg_top[new_peg]] = selected_disk;
            disks[selected_disk].peg = new_peg;
        }
    }
}

int main() {
    gfx_init();
    for (int i = 0; i < NUM_DISKS; i++) {
        disks[i].size = NUM_DISKS - i;
        disks[i].peg = 2;
        pegs[2][i] = i;
    }
    peg_top[2] = NUM_DISKS - 1;
    draw_hanoi();
    while (1) {
        int key = gfx_getkey();
        if (key == SDLK_LEFT && selected_disk > 0) selected_disk--;
        if (key == SDLK_RIGHT && selected_disk < NUM_DISKS - 1) selected_disk++;
        if (key == SDLK_1) move_disk(0);
        if (key == SDLK_2) move_disk(1);
        if (key == SDLK_3) move_disk(2);
        draw_hanoi();
    }
    return 0;
}
