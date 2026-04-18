#include "vfr_init.h"
#include "src\src\hardware\hardware.h"

bool rLED = false;

void vfr_init(){
    rLED = true;
}

void vfr_loop(){
    if (rLED == true){
        *GPSET0 = (1 << 18);
    }
    else{
        *GPCLR0 = (1 << 18);
    }

}
