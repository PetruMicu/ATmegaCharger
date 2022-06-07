/*================================================================================================================
* Project: AtmegaCharger
* Platform: AvrStudio4
* MCU: ATmega164A
* Subject: Project2 (P2)
* Owners: Petru Micu, Andreea-Ioana Andrei
* Professor: Adrian Paun
================================================================================================================*/

#include <mega164A.h>
#include <delay.h>
#include <twi.h>
#include <alcd_twi.h>
#include "PrimitiveTypeDefs.h"
#ifndef HW_H
#define HW_H

// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))
/**
* @brief Active low logic high
* @implements	DEFINE LVL_HIGH
*/
#define LVL_HIGH 0u
/**
* @brief Active low logic low
* @implements	DEFINE LVL_LOW
*/
#define LVL_LOW 1u

/**
* @brief Enumeration of hardware pieces that need an output
* @implements	enum HW_OUT
*/

typedef enum
{
    GREED_LED = 0u,
    RED_LED,
    ON_OFF_LED, // PORTD6
    POWER_RELAY,
    BATTERY_RELAY
}HW_OUT;

/**
* @brief Enumeration of hardware pieces that provide an analog input
* @implements	enum HW_AIN
*/
typedef enum
{
    TMP_SENS = 0u,
    CURR_SENS = 1u
}HW_AIN;

/**
* @brief Enumeration of hardware pieces that provide a digital input
* @implements	enum HW_DIN
*/
typedef enum
{
    INTERFACE_BTN = 0u, // Button at PORTD5
    DIGITAL_TMP_SENSOR
}HW_DIN;

/**
* @brief Structure containing all data read from external hardware
* @implements	struct HW_DataCollection
*/
typedef struct
{
    uint16 current;
    uint16 temperature;
    //add more if needed
}HW_DataCollection;

/**
* @brief Union that emulates a register for easy bit access
* @implements	union HW_REG8
*/
typedef union
{
    uint8_t reg8;
    struct reg{
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
        uint8_t bit4 : 1;
        uint8_t bit5 : 1;
        uint8_t bit6 : 1;
        uint8_t bit7 : 1;
    };
}HW_REG8;

/**
* @brief Sets the registers accordingly
 * @implements	HW_Init(void)
*/
void HW_Init(void);

/**
* @brief Controls logic level of an external device
 * @implements	HW_SetOutput(HW_OUT controlUnit, uint8 logicLevel)
*/
void HW_SetOutput(HW_OUT controlUnit, uint8 logicLevel);

/**
* @brief Reads digital input of external device
 * @implements	HW_ReadInput(HW_IN controlUnit)
*/
uint8 HW_ReadInput(HW_DIN controlUnit);

/**
* @brief Reads analog value from an external sensor and converts it via ADC into uint16
 * @implements	HW_ReadSensor(HW_AIN sensor)
*/
uint16 HW_ReadSensor(HW_AIN sensor);
/**
* @brief Controls the interface of LCD
 * @implements	void LCD_interface1(uint8 logicLevel)
*/
void LCD_interface1(void);

/**
* @brief Controls the interface of LCD
 * @implements	void LCD_interface2(uint8 logicLevel)
*/
void LCD_interface2();

/**
* @brief Initialize the LCD
 * @implements	void LCD_init(void);
*/
void LCD_init(void);


#endif /* HW_H */