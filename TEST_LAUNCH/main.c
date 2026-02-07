#include "F2806x_Device.h"
#include "F2806x_Examples.h"

/**
 * main.c
 */
void main(void)
{
    InitSysCtrl();

    DINT;

    InitGpio();

    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;

    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

    EDIS;

    for(;;){
        GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;

        DELAY_US(1000000);

        GpioDataRegs.GPBSET.bit.GPIO34 = 1;

        DELAY_US(1000000);
    }

}
