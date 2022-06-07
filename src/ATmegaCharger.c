/*================================================================================================================
* Project: AtmegaCharger
* Platform: AvrStudio4
* MCU: ATmega164A
* Subject: Project2 (P2)
* Owners: Petru Micu, Andreea-Ioana Andrei
* Professor: Adrian Paun
================================================================================================================*/

/*================================================================================================================
*									INCLUDE FILES
================================================================================================================*/
#include "../include/HW.h"
#include "../include/PrimitiveTypeDefs.h"
#include <delay.h>
#include <math.h>
extern uint8_t powerRelay;
extern uint8_t batteryRelay;
/**
* Main Function of the project.
*
*/
void ATmegaCharger()
{
    uint16_t temperature = 0, current = 0;
    // Test API functionality
    HW_Init();
    LCD_Init();
    while(1)
    {
        LCD_Interface();
        delay_ms(500);
        lcd_clear();

    }
}