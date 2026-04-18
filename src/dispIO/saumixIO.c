#include "saumixIO.h"
#include "C:\Users\ak\Mini PC\src\src\stdDatatypes.h"
#include "src/src/hardware/hardware.h"


void displ(char c) {
    while (*UART0_FR & (1 << 5)) {

    }


    *UART0_DR = c;
}




void k_display_print(const char* str) {
    while (*str) {
      displ(*str);
      str++;
    }
}

void k_log(int status, const char* msg) {
    if (status == 0) {
        // [OK] in Grün
        k_display_print(ANSI_GREEN "[OK] " ANSI_RESET);
    } else {
        // [ERR] in Rot
        k_display_print(ANSI_RED "[ERR] " ANSI_RESET);
    }
    k_display_print(msg);
    k_display_print("\n");
}
