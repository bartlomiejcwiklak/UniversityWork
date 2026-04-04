#include "primlib.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PEG_NUMBER 3
#define DISC_NUMBER 3
#define PEG_WIDTH 20
#define PEG_HEIGTH 200
#define FLOOR_HEIGHT 25

void draw_floor();
void draw_pegs(int pegs_count);
void draw_discs(int peg_count, int disc_count);
double get_disc_height(int disc_count);
double get_disc_width(int peg_count, int disc_count);
double get_y_cordinates(int current_iteration, int disc_count);
void game_init();
void listen_for_keys();
int get_disc_index_from(int row_to_check);
int get_disc_index_to(int row_to_check);
int rellocate_disc(int from, int to);
int get_first_key();
int get_second_key();
void print_peg_arr();
void print_getKey();
int check_game_status();

// Prototype for the new animation function
void animate_move(int from, int to, int from_index, int to_index, int disk_value);

int peg_arr[PEG_NUMBER][DISC_NUMBER];

int main(int argc, char* argv[])
{	
    if (gfx_init()) {
        exit(3);
    }
    
    game_init();

    // Initial drawing loop (for 100 frames)
    for (int i = 0; i < 100; i++) {
        gfx_filledRect(0, 0, gfx_screenWidth(), gfx_screenHeight(), BLACK);
        draw_floor();
        draw_pegs(PEG_NUMBER);
        draw_discs(PEG_NUMBER, DISC_NUMBER);
        gfx_updateScreen();
        SDL_Delay(10);
        
        if (gfx_pollkey() == SDLK_ESCAPE) {
            exit(0);
        } 
    }
    
    listen_for_keys();
    
    return 0;
}

void game_init() {
    for (int i = 0; i < PEG_NUMBER; i++) {
        for (int j = 0; j < DISC_NUMBER; j++) {
            peg_arr[i][j] = 0;
        }
    }
    
    // Initialize the first peg with disks in decreasing order (largest at the bottom)
    for (int i = 0; i < DISC_NUMBER; i++) {
        peg_arr[0][i] = DISC_NUMBER - i;
    }
    
    print_peg_arr();
}

int get_first_key() {
    int peg_from = gfx_getkey() - '0';
    if (peg_from >= 1 && peg_from <= PEG_NUMBER) {
        return peg_from - 1; 
    }
    return -1;
}

int get_second_key() {
    int peg_to = gfx_getkey() - '0';
    if (peg_to >= 1 && peg_to <= PEG_NUMBER) {
        return peg_to - 1; 
    }
    return -1;
}

void listen_for_keys() {
    while (1) {
        int first_key = get_first_key();
        if (first_key == -1) continue;
        
        int second_key = get_second_key();
        if (second_key == -1) continue;
        
        rellocate_disc(first_key, second_key);
    }
}

int rellocate_disc(int from, int to) {
    int from_index = get_disc_index_from(from);
    int to_index = get_disc_index_to(to);

    if (from_index == -1) return 0; 
    
    int picked_disc = peg_arr[from][from_index];
    int comparison_disc = (to_index == 0) ? 0 : peg_arr[to][to_index - 1];

    if (comparison_disc == 0 || picked_disc < comparison_disc) {
        // Remove the disk from the source peg
        peg_arr[from][from_index] = 0;
        
        // Animate the disk moving from peg "from" to peg "to"
        animate_move(from, to, from_index, to_index, picked_disc);
        
        // After animation, place the disk in the destination peg
        peg_arr[to][to_index] = picked_disc;
        print_peg_arr();
        
        if (check_game_status()) {
            gfx_textout(gfx_screenWidth() / 2, gfx_screenHeight() / 2, "Congratulations, YOU WON!", RED);
            gfx_updateScreen();
        }
        
        return 1;
    }
    return 0;
}

int get_disc_index_from(int row_to_check) {
    for (int i = DISC_NUMBER - 1; i >= 0; i--) {
        if (peg_arr[row_to_check][i] != 0) {
            return i;
        }
    }
    return -1;
}

int get_disc_index_to(int row_to_check) {
    for (int i = 0; i < DISC_NUMBER; i++) {
        if (peg_arr[row_to_check][i] == 0) {
            return i;
        }
    }
    return DISC_NUMBER; 
}

int check_game_status() {
    for (int i = 1; i < PEG_NUMBER; i++) {
        int expected_disc = DISC_NUMBER;
        int valid = 1; 

        for (int j = 0; j < DISC_NUMBER; j++) {
            if (peg_arr[i][j] != expected_disc) {
                valid = 0;
                break;
            }
            expected_disc--;
        }

        if (valid) {
            return 1;
        }
    }
    return 0;
}

void draw_floor(){
    gfx_filledRect(
        0,
        gfx_screenHeight(),
        gfx_screenWidth(),
        gfx_screenHeight() - FLOOR_HEIGHT,
        GREEN
    );
}

void draw_pegs(int pegs_count){
    double distance_between_pegs = 0;
    
    for (int i = 0; i < pegs_count; i++) {
        distance_between_pegs += gfx_screenWidth() / (pegs_count + 1);
        
        gfx_filledRect(
            distance_between_pegs - PEG_WIDTH / 2, 
            gfx_screenHeight() - FLOOR_HEIGHT - PEG_HEIGTH, 
            distance_between_pegs + PEG_WIDTH / 2,
            gfx_screenHeight() - FLOOR_HEIGHT,
            RED
        );
    }
}

double get_disc_height(int discs_count){
    return PEG_HEIGTH / discs_count;
}

double get_disc_width(int peg_count, int disc_count){
    return gfx_screenWidth() / (peg_count + 1) / disc_count;
}

double get_y_cordinates(int current_iteration, int disc_count) {
    return gfx_screenHeight() - FLOOR_HEIGHT - (current_iteration) * get_disc_height(disc_count) * 0.8;
}

void draw_discs(int peg_count, int disc_count){    
    for (int i = 0; i < disc_count; i++){
        gfx_filledRect(
            gfx_screenWidth() / (peg_count + 1) - (disc_count - i) * get_disc_width(peg_count, disc_count) * 0.5 - PEG_WIDTH / 1.75,
            get_y_cordinates(i, DISC_NUMBER),
            gfx_screenWidth() / (peg_count + 1) + (disc_count - i) * get_disc_width(peg_count, disc_count) * 0.5 + PEG_WIDTH / 1.75,
            get_y_cordinates(i + 1, DISC_NUMBER),
            YELLOW
        );
        
        gfx_rect(
            gfx_screenWidth() / (peg_count + 1) - (disc_count - i) * get_disc_width(peg_count, disc_count) * 0.5 - PEG_WIDTH / 1.75,
            get_y_cordinates(i, DISC_NUMBER),
            gfx_screenWidth() / (peg_count + 1) + 1 + (disc_count - i) * get_disc_width(peg_count, disc_count) * 0.5 + PEG_WIDTH / 1.75,
            get_y_cordinates(i + 1, DISC_NUMBER),
            BLACK
        );
    }
}

void print_getKey() {
    int key = gfx_getkey() - '0';
    
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    
    sprintf(buffer, "Wcisniety klawisz: %d\n", key);
    
    printf("%s", buffer);
    fflush(stdout);
}

void print_peg_arr() {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    char *ptr = buffer;

    ptr += sprintf(ptr, "\nAktualny stan peg_arr:\n");

    for (int i = 0; i < PEG_NUMBER; i++) {
        for (int j = 0; j < DISC_NUMBER; j++) {
            ptr += sprintf(ptr, "%d ", peg_arr[i][j]);
        }
        ptr += sprintf(ptr, "\n");
    }

    printf("%s", buffer);
    fflush(stdout);
}

// The animation function that moves a disk from one peg to another
void animate_move(int from, int to, int from_index, int to_index, int disk_value) {
    // Animation settings:
    const int frames = 20;       // number of frames for each phase
    const int delay_ms = 15;     // delay between frames in milliseconds
    double peg_spacing = (double) gfx_screenWidth() / (PEG_NUMBER + 1);
    
    // Compute the center x coordinates for source and destination pegs:
    double start_x = (from + 1) * peg_spacing;
    double end_x   = (to   + 1) * peg_spacing;
    
    // Determine the current (source) and target vertical positions.
    double start_y = (get_y_cordinates(from_index, DISC_NUMBER) + get_y_cordinates(from_index + 1, DISC_NUMBER)) / 2.0;
    double end_y   = (get_y_cordinates(to_index, DISC_NUMBER)   + get_y_cordinates(to_index + 1, DISC_NUMBER)) / 2.0;
    
    // Set a fixed “lift” height (adjust as needed)
    double lift_y = gfx_screenHeight() * 0.2;
    
    // Compute the moving disk's dimensions.
    double min_disk_width = peg_spacing * 0.3;
    double max_disk_width = peg_spacing * 0.8;
    double disk_width = min_disk_width + ((double) disk_value / DISC_NUMBER) * (max_disk_width - min_disk_width);
    double disk_height = (PEG_HEIGTH / (double) DISC_NUMBER) * 0.8;

    // Phase 1: Lift the disk upward from start_y to lift_y.
    for (int i = 0; i <= frames; i++) {
        double t = (double) i / frames;
        double current_y = start_y + (lift_y - start_y) * t;
        // Redraw background:
        gfx_filledRect(0, 0, gfx_screenWidth(), gfx_screenHeight(), BLACK);
        draw_floor();
        draw_pegs(PEG_NUMBER);
        draw_discs(PEG_NUMBER, DISC_NUMBER);
        // Draw the moving disk at the starting peg's x coordinate:
        gfx_filledRect(
            start_x - disk_width/2,
            current_y - disk_height/2,
            start_x + disk_width/2,
            current_y + disk_height/2,
            YELLOW
        );
        gfx_rect(
            start_x - disk_width/2,
            current_y - disk_height/2,
            start_x + disk_width/2,
            current_y + disk_height/2,
            BLACK
        );
        gfx_updateScreen();
        SDL_Delay(delay_ms);
    }

    // Phase 2: Move horizontally from start_x to end_x while keeping lift_y.
    for (int i = 0; i <= frames; i++) {
        double t = (double) i / frames;
        double current_x = start_x + (end_x - start_x) * t;
        gfx_filledRect(0, 0, gfx_screenWidth(), gfx_screenHeight(), BLACK);
        draw_floor();
        draw_pegs(PEG_NUMBER);
        draw_discs(PEG_NUMBER, DISC_NUMBER);
        gfx_filledRect(
            current_x - disk_width/2,
            lift_y - disk_height/2,
            current_x + disk_width/2,
            lift_y + disk_height/2,
            YELLOW
        );
        gfx_rect(
            current_x - disk_width/2,
            lift_y - disk_height/2,
            current_x + disk_width/2,
            lift_y + disk_height/2,
            BLACK
        );
        gfx_updateScreen();
        SDL_Delay(delay_ms);
    }

    // Phase 3: Lower the disk from lift_y to the destination y position (end_y).
    for (int i = 0; i <= frames; i++) {
        double t = (double) i / frames;
        double current_y = lift_y + (end_y - lift_y) * t;
        gfx_filledRect(0, 0, gfx_screenWidth(), gfx_screenHeight(), BLACK);
        draw_floor();
        draw_pegs(PEG_NUMBER);
        draw_discs(PEG_NUMBER, DISC_NUMBER);
        gfx_filledRect(
            end_x - disk_width/2,
            current_y - disk_height/2,
            end_x + disk_width/2,
            current_y + disk_height/2,
            YELLOW
        );
        gfx_rect(
            end_x - disk_width/2,
            current_y - disk_height/2,
            end_x + disk_width/2,
            current_y + disk_height/2,
            BLACK
        );
        gfx_updateScreen();
        SDL_Delay(delay_ms);
    }
}
