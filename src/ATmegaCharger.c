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
#include "../include/GPIO.h"
#include "../include/PrimitiveTypeDefs.h"
#include <delay.h>
#include <math.h>

/**
* Main Function of the project.
*
*/
void ATmegaCharger()
{
    // Test API functionality
    HW_Init();
    HW_SetOutput(RELAY1, LVL_HIGH);
    //HW_SetOutput(RELAY2, LVL_HIGH);
    HW_SetOutput(RED_LED, LVL_HIGH);
    LCD_init();

    while(1)
    {

    }
}