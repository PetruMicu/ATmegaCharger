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
    //LCD_interface2();

    while(1)
    {
       //lcd_printf("%u",HW_ReadSensor(CURR_SENS1));
       uint16 r2,r;
       r = HW_ReadSensor(CURR_SENS1);
       //delay_ms(1);
       //r2 = HW_ReadSensor(CURR_SENS2);
       lcd_printf("%u",r);
       delay_ms(3000); 
       lcd_clear();
//        uint32 temperature,copy, resistance,rawValue;
//        uint8 count, index, i;
//        char text[16] = "TEMP: ";
//        lcd_clear();
//        rawValue = HW_ReadSensor(CURR_SENS1);
//        if(rawValue != 0u)
//            resistance = ((uint32)1000u * (uint32)(1023u/rawValue - 1));
//        else
//            resistance = 546789;
//        //temperature = (3950.0u*300.0u) / ((double)3950u + ((double)300u * (double)log(resistance / 10000u)));
//        copy = rawValue;
//        temperature = 1u;
//        count = 0u, index = 6u;
//        while(copy)
//        {
//            temperature = temperature*10 + copy % 10;
//            count++;
//            copy /= 10u;
//        }
//        for(i = 0; i < count; i++)
//        {
//           text[index] = (temperature % 10) + '0';
//           temperature /= 10;
//           index++;
//        }
//        text[index] = '\0';
//        lcd_puts(text);
//        delay_ms(1000);
    }
}