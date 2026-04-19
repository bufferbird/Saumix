#include "src/src/hardware/hardware.h"
#include "src/src/hardware/communication/esp_comm.h"
#include "src/src/kernelthings/scheduler.h"
#include "src/src/init.h"
#include "src/klib.h"
#include "src/stdDatatypes.h"
#include "src/src/security/securitycore.h"
#include "src/src/stdarg.h"
#include "src/src/dispIO/saumixIO.h"
#include "src/src/userapps/terminal.h"
#include "src/src/security/mmu/mmu.h"

// --- Hardware Absicherungen ---
#ifndef MAILBOX_READ
#define MAILBOX_READ 0x3F00B880
#endif

#ifndef MAILBOX_STATUS
#define MAILBOX_STATUS 0x3F00B898
#endif

#ifndef MAILBOX_WRITE
#define MAILBOX_WRITE 0x3F00B8A0
#endif

// Globaler Pointer, damit er nach vga_init() noch existiert
uint32_t* fb_ptr = 0;
__attribute__((aligned(16))) uint32_t mailbox[32];

extern unsigned char __bss_start;
extern unsigned char __bss_end;

static void bss_init(void) {
    unsigned char *dst = &__bss_start;
    while (dst < &__bss_end) {
        *dst++ = 0;
    }
}

static void vga_init(void){
    mailbox[0] = 35 * 4;  
    mailbox[1] = 0;        

    mailbox[2] = 0x00048003; 
    mailbox[3] = 8;
    mailbox[4] = 8;
    mailbox[5] = 1024; // Breite
    mailbox[6] = 768;  // Höhe

    mailbox[7] = 0x00048004;
    mailbox[8] = 8;
    mailbox[9] = 8;
    mailbox[10] = 1024;
    mailbox[11] = 768;

    mailbox[12] = 0x00048005;
    mailbox[13] = 4;
    mailbox[14] = 4;
    mailbox[15] = 32;

    mailbox[16] = 0x00040001;
    mailbox[17] = 8;
    mailbox[18] = 8;
    mailbox[19] = 4096;
    mailbox[20] = 0; 

    mailbox[21] = 0; 

    // Senden
    while (*(volatile uint32_t*)MAILBOX_STATUS & 0x80000000);
    *(volatile uint32_t*)MAILBOX_WRITE = ((uint32_t)(uintptr_t)mailbox & ~0xF) | 8;

    // Warten
    while (1) {
        while (*(volatile uint32_t*)MAILBOX_STATUS & 0x40000000);
        uint32_t response = *(volatile uint32_t*)MAILBOX_READ;
        if ((response & 0xF) == 8) break;
    }

    // Pointer global speichern (Maskierung für CPU-Zugriff)
    fb_ptr = (uint32_t*)(uintptr_t)(mailbox[20] & 0x3FFFFFFF);
}

/*Soo, here we are, we just need to init last things, like the rMCPU wich controlls the vfr, yes, a register controlling registers;
  am i a genius, or a maniac?
*/

static void boot_and_last_inits(){
    k_displ_print("[SYS] Last setups, please wait.");
    int rMCPU = 1;     
}

// k_main() braucht einen Rückgabetyp, meist void
void k_main(){
    bss_init();      // 1. Zuerst BSS (leert auch das mailbox array)
    vga_init();      // 2. Dann Grafik
    
    // Ab hier ist fb_ptr einsatzbereit
    init_secure();
    boot_and_last_inits();
    security_loop();
    init();
    vfr_init();
    schedule();
    
    asm volatile("sti");

    while(1) {
        asm volatile("hlt");
    }
}

