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

static void __init__(void){
    // ...
}

k_main(){
    boot_init_last();
    init_secure();
    security_loop();

    vfr_init();
    schedule();
    __init__();
}
