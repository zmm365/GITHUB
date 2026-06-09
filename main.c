#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"

void Automat(void)
{
    enum LedState {STOP, LEFT_DIRECTION, RIGHT_DIRECTION};
    static enum LedState eLedState = STOP;
    static unsigned char ucClockDivider = 0; 
    
    enum KeyboardState eCurrentKey = eKeyboardRead();

    switch(eLedState)
    {
        case STOP:
            if(eCurrentKey == BUTTON_0) {
                eLedState = LEFT_DIRECTION;
                ucClockDivider = 0;
            } else if(eCurrentKey == BUTTON_2) {
                eLedState = RIGHT_DIRECTION;
                ucClockDivider = 0;
            } else {
                eLedState = STOP;
            }
            break;

        case LEFT_DIRECTION:
            if(eCurrentKey == BUTTON_1) {
                eLedState = STOP;
            } else {
                eLedState = LEFT_DIRECTION;
                
                ucClockDivider++;
                if(ucClockDivider >= 12) {
                    LedStepLeft();
                    ucClockDivider = 0;
                }
            }
            break;

        case RIGHT_DIRECTION:
            if(eCurrentKey == BUTTON_1) {
                eLedState = STOP;
            } else {
                eLedState = RIGHT_DIRECTION;
                
                ucClockDivider++;
                if(ucClockDivider >= 12) { 
                    LedStepRight();
                    ucClockDivider = 0;
                }
            }
            break;
            
        default:
            eLedState = STOP;
            break;
    }
}


int main (void){
    unsigned int iMainLoopCtr = 0;
    
    LedInit();
    KeyboardInit();
    Timer0Interrupts_Init(20000, &Automat);

    while(1){
        iMainLoopCtr++;
				iMainLoopCtr++;
				iMainLoopCtr++;
				iMainLoopCtr++;
    }
}
