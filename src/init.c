// Copyright (c) by bufferbird
// GLP License
// Modul Description: Init's the UART and the other things wich are needed

#include "stdDatatypes.h"
#include "src/src/dispIO/saumixIO.h"
#include "src/src/hardware/hardware.h"
#include "src/hardware/communication/esp_comm.h"

void init() {

    *UART0_CR = 0; 
    k_log_init(0, "UART0_CR cleared");

    *UART0_IBRD = 26;
    *UART0_FBRD = 3;
    
    if (*UART0_IBRD == 26) {
        k_log_init(0, "Baudrate registers loaded (115200)");
    } else {
        k_log_init(1, "Hardware Register Mismatch!");
    }

    *UART0_LCRH = (1 << 4) | (1 << 5) | (1 << 6);
    k_log_init(0, "LCRH (8-bit, FIFO) configured");

    *UART0_CR = (1 << 0) | (1 << 8) | (1 << 9);
    
    k_display_print(ANSI_YELLOW "[SYS] " ANSI_RESET "UART0 is now online.\n\n");

    k_display_print(ANSI_BOLD "Saumix Kernel v1.0 starting...\n" ANSI_RESET);
    
    k_display_print("Loading modules: [########........] 25%\r");
    
    
    k_display_print("Loading modules: [###############.] 75%\r");
    k_display_print("Loading modules: [################] 100%\n");

    to_esp_send("connect");
    k_displ_print("Saumix now has WLAN, Bluetooth and Printing Stack");

    k_display_print(ANSI_BOLD ANSI_GREEN "Finished! System ready." ANSI_RESET "\n");
}
