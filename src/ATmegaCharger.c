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
/**
* Main Function of the project.
*
*/
void ATmegaCharger()
{
    uint16_t temperature = 0, current = 0;
    // Test API functionality
    HW_Init();
    HW_SetOutput(POWER_RELAY, LVL_HIGH);
    HW_SetOutput(RED_LED, LVL_HIGH);
    LCD_init();
    while(1)
    {
//        HW_SetOutput(BATTERY_RELAY, LVL_HIGH);
//        HW_SetOutput(GREED_LED, LVL_HIGH);
//        delay_ms(1000);
//        HW_SetOutput(BATTERY_RELAY, LVL_LOW);
//        HW_SetOutput(GREED_LED, LVL_LOW);
//        delay_ms(1000);

    }
}