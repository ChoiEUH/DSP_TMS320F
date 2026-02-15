#include "F2806x_Device.h"
#include "F2806x_Examples.h"

volatile Uint16 ADCRaw = 0;
volatile Uint16 AdcResult12 = 0;

static void ADC_Init(void)
{
    InitSysCtrl();
    InitAdc();

    EALLOW;
    AdcRegs.ADCSOC0CTL.bit.CHSEL   = 7;
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 0;
    AdcRegs.ADCSOC0CTL.bit.ACQPS   = 19;
    EDIS;
}

static inline void ADC_Read(void)
{

    AdcRegs.ADCSOCFRC1.bit.SOC0 = 1;

    DELAY_US(5);

    ADCRaw = AdcResult.ADCRESULT0;

    AdcResult12 = (ADCRaw >> 4) & 0x0FFF; //컨버팅 된 RAW값을 하위 정렬 시킨 후 마스킹 실시
}

int main(void)
{
    DINT;
    InitPieCtrl();
    IER = 0;
    IFR = 0;
    InitPieVectTable();

    ADC_Init();

    for(;;)
    {
        ADC_Read();
        DELAY_US(1000);
    }
}
