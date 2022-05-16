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
#include "../include/LCD.h"
#include <delay.h>
#include <stdio.h>
#include <string.h>
/*================================================================================================================
*									LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
================================================================================================================*/

/*================================================================================================================
*									LOCAL MACROS
================================================================================================================*/

/*================================================================================================================
*									LOCAL CONSTANTS
================================================================================================================*/

/*================================================================================================================
*									GLOBAL CONSTANTS
================================================================================================================*/
// Globally enable interrupts
#asm("sei")
/*================================================================================================================
*									GLOBAL VARIABLES
================================================================================================================*/
// buttonState defines what battery type is selected
uint8 btn = LVL_LOW;
/*================================================================================================================
*									LOCAL FUNCTION PROTOTYPES
================================================================================================================*/

/*================================================================================================================
*									LOCAL FUNCTIONS
================================================================================================================*/

/*================================================================================================================
*									GLOBAL FUNCTIONS
================================================================================================================*/
/**
* Initialize the LCD and I2C.
*
*/
void LCD_init()
{
    twi_master_init(100);
    lcd_twi_init(0x27,16);
    //lcd_clear();
}

/**
* Shows the first interface when the button is pressed.
*
*/
void LCD_interface1()
{
    uint16 resultLiPo, resultNiMh, temperatureLiPo, temperatureNiMh;
    switch (btn)
    {
        case LVL_HIGH:
            lcd_printf("LiPo ");
            resultLiPo = HW_ReadSensor(CURR_SENS1);
            //TODO: find the formula for %
            lcd_printf("%u%%", resultLiPo);
            lcd_gotoxy(0,1);
            lcd_printf("Temp");
            temperatureLiPo = HW_ReadSensor(TMP_SENS);
            lcd_printf("%uC ", temperatureLiPo);
            lcd_printf("Fan:");
            break;
        case LVL_LOW:
            lcd_printf("NiMh ");
            resultNiMh = HW_ReadSensor(CURR_SENS2);
            //TODO: find the formula for %
            lcd_printf("%u%%", resultNiMh);
            lcd_gotoxy(0,1);
            lcd_printf("Temp:");
            temperatureNiMh = HW_ReadSensor(TMP_SENS);
            lcd_printf("%uC ", temperatureNiMh);
            lcd_printf("Fan:");
            break;
        default: //do nothing
    }
}
void LCD_interface2()
{
    uint16 resultLiPo, resultNiMh, temperatureLiPo, temperatureNiMh;
    switch (btn)
    {
        case LVL_HIGH:
            lcd_printf("LiPo ");
            resultLiPo = HW_ReadSensor(CURR_SENS1);
            //TODO: calculate the current
            lcd_printf("%u mA", resultLiPo);
            lcd_gotoxy(0,1);
            lcd_printf("Temp");
            temperatureLiPo = HW_ReadSensor(TMP_SENS);
            lcd_printf("%uC ", temperatureLiPo);
            lcd_printf("Fan:");
            break;
        case LVL_LOW:
            lcd_printf("NiMh ");
            resultNiMh = HW_ReadSensor(CURR_SENS2);
            //TODO: calculate the current
            lcd_printf("%u mA", resultNiMh);
            lcd_gotoxy(0,1);
            lcd_printf("Temp:");
            temperatureNiMh = HW_ReadSensor(TMP_SENS);
            lcd_printf("%uC ", temperatureNiMh);
            lcd_printf("Fan:");
            break;
        default: //do nothing
    }
}