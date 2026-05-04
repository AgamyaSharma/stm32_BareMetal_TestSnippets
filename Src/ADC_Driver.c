/*
 * EARLY PROOF OF CONCEPT (JAN 2026)
 * Raw memory-mapped ADC test before building the hardware abstraction layer.
 * Keeping this here for reference!
 */
#include <stdint.h>
# include "stm32f302r8.h"
 volatile uint32_t data1;
 volatile uint32_t data2;
int main(void)
{
    uint32_t *RccAhbReg = (uint32_t*) 0x40021014;//18
    uint32_t *GPIOx_MODER_PB0 = (uint32_t*)0x48000400;//0-1
    uint32_t *GPIOx_MODER_PA4 = (uint32_t*) 0x48000000;//0-1
    uint32_t *ClockcontrolReg = (uint32_t*) 0x50000308;
    uint32_t *AdcControlReg = (uint32_t*) 0x50000008;//16-17 for clock 11 hckl/4
    uint32_t *SampleTimeReg1 = (uint32_t*) 0x50000014;
    uint32_t *SampleTimeReg2 = (uint32_t*) 0x50000018;
    uint32_t *SequenceReg = (uint32_t*) 0x50000030;
    uint32_t *modeSelectionReg = (uint32_t*) 0x500000B0;
    volatile uint32_t *irsReg = (uint32_t*) 0x50000000;
    uint32_t *adcDatareg = (uint32_t*) 0x50000040;
    uint32_t *AdcConfigReg = (uint32_t*) 0x5000000C;
    // START OF GPIO CONFIG
    *RccAhbReg |= ((1<<18) | (1<<28)|(1<17));//enabling the clock of ADC and the GPIOs, 28-ADC, 17 AND 18 FOR AND B RESPECTIVELY
    *GPIOx_MODER_PB0 |= ((1) |(1<<1));
    *GPIOx_MODER_PA4 |= ((1<<8)|(1<<9));
  // END OF GPIO CONFIG
    *ClockcontrolReg |= ((1<<16) | (1<<17));




    *AdcControlReg &= ~((1<<29)|(1<<28));
    *AdcControlReg |= (1<<28);//voltage regulation
    for(volatile int i=1; i<=1000;i++){
    	__asm("nop");

    }
    *AdcControlReg &= ~(1<<30);//and mode of cal
    *AdcControlReg &= ~(1<<31);
    while(*AdcControlReg & (1<<31));//(polling)
    *AdcControlReg |= (1<<31);
    while(*AdcControlReg & (1<<31));
    *AdcConfigReg |= (1 << 14);
    *SampleTimeReg1 &= ~((1<<15)|(1<<16)|(1<<17));
    *SampleTimeReg1 |= ((1<<15)|(1<<16));
    *SampleTimeReg2 &= ~((1<<3)|(1<<4)|(1<<5));
    *SampleTimeReg2 |= ((1<<4)|(1<<5));

    *SequenceReg &= ~((1)|(1<<1)|(1<<2)|(1<<3));
    *SequenceReg |= ((1));// 6 7 8 9 10
    *SequenceReg &= ~((1<<6)|(1<<7)|(1<<8)|(1<<10)|(1<<12)|(1<<13)|(1<<14)|(1<<15));
    *SequenceReg |= ((1<<9)|(1<<7)|(1<<6)|(1<<14)|(1<<12));
    *modeSelectionReg &= ~(1<<8);// mode selection



    while(*AdcControlReg & (1<<31));
    *AdcControlReg |= (1);
    // enable and start
    while(!(*irsReg & (1)));
    while(1){
    *AdcControlReg |= (1<<2);
    while(!(*irsReg & (1<<2)));

    data1 = *adcDatareg;
    while(!(*irsReg & (1<<2)));
    data2 = *adcDatareg;
    }
	for(;;);
}


