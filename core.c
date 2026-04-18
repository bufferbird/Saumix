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

extern unsigned char __bss_start;
extern unsigned char __bss_end;

static void bss_init(void) {
    unsigned char *dst = &__bss_start;
    while (dst < &__bss_end) {
        *dst++ = 0;
    }
}

static void __register_setup(void){
    
}

/*       
    Here we are, we just need to init last things like the register Main Register Controlling Unit, so the registers get 
    Controlled, yes, by a register, dont ask
*/

static void boot_and_last_inits(){
    k_displ_print("[SYS] Last setups, please wait.");
    int rMRCU = 1; 
}

k_main(){
    bss_init();
    boot_init_last();
    init_secure();
    security_loop();
    init();
    vfr_init();
    schedule();
}
