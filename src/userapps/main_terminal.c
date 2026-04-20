/*
  Copyright (c) bufferbird, Saumix
  GPL License
*/

/* sorry for always writing this, im paranoid for people steeling code */

#include "src/stdDatatypes.h"
#include "src/kernelthings/scheduler.h"
#include "src/dispIO/saumixIO.h"
#include "core.c"
#include "src/userapps/filesystem/exectables/shb.h"
#include "src/hardware/communication/esp_comm.h" // not available on github for you, but soon it will be 'published'
#include "src/font.h"

 /*
   Sooo, this were more includes then core.c but ok, now were finally up to date with includes, and kann start 
   with really programming xD
   First some Variables...
 */



int y_pos = 50;
int x_pos = 5;
int terminal_window_height = 70;
int cmd_line_width = 60;
int cmd_line_height = 10;

bool everything_went_good_in_init = false; // weise vorraussicht

static void init_terminal(void) {
    draw_terminal();// not finished yet, okaaay
    
    cursor_pos = y_pos; 

    if (get_display_status() != NULL) { // yes, also unfinish, but chill, it isnt as deep
        everything_went_good_in_init = true;
    } else {
        kprintf("Error %s occured", get_error());
    }

    if (everything_went_good_in_init == true) {
        system_window("Sys Info", "Successfully Setted Up the Terminal. Ready for user input");
    }
}

bool terminal_main() {
    init_terminal();
    if (everything_went_good_in_init) {
        terminal_loop(); // Schande über mein Haupt, aber wir rufen sie wenigstens auf
        return true;
    }
    return false;
}
