#include "timer_interrupts.h"
#include <LPC21xx.H>

// TIMER 0
#define mCOUNTER_ENABLE   0x00000001
#define mCOUNTER_RESET    0x00000002

// CompareMatch
#define mINTERRUPT_ON_MR0 0x00000001
#define mRESET_ON_MR0     0x00000002
#define mMR0_INTERRUPT    0x00000001

// VIC (Vector Interrupt Controller)
#define VIC_TIMER0_CHANNEL_NR 4
#define mIRQ_SLOT_ENABLE      0x00000020

void (*ptrTimer0InterruptFunction)(void);

/**********************************************/
// Procedura obslugi przerwania od Timera 0
__irq void Timer0IRQHandler(){
    T0IR = mMR0_INTERRUPT;
    if(ptrTimer0InterruptFunction != 0){
        ptrTimer0InterruptFunction();
    }
    VICVectAddr = 0x00;
}

/**********************************************/
void Timer0Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void)){ 
    ptrTimer0InterruptFunction = ptrInterruptFunction;

    // Interrupts
    VICIntEnable |= 0x0000000C; // Ustawia bity 2 i 3 (czyli 0x0C) za pomoca sumy bitowej
    VICVectCntl0  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;
    VICVectAddr0  = (unsigned long)Timer0IRQHandler;

    // Match module
    T0MR0  = 15 * uiPeriod;
    T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0);
    
		// Timer
		T0TCR |= mCOUNTER_ENABLE; 			//start
}
