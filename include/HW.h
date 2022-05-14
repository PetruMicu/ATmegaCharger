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
#include "PrimitiveTypeDefs.h"

#ifndef HW_H
#define HW_H


/*================================================================================================================
*									CONSTANTS
================================================================================================================*/

/*================================================================================================================
*									DEFINES AND MACROS
================================================================================================================*/

/*================================================================================================================
*									ENUMS
================================================================================================================*/
/**
* @brief Enumeration of hardware pieces that need an output
* @implements	enum HW_OUT
*/

typedef enum
{
    GREED_LED = 0u,
    RED_LED,
    RELAY1,
    RELAY2
}HW_OUT;

/**
* @brief Enumeration of hardware pieces that provide an analog input
* @implements	enum HW_AIN
*/
typedef enum
{
    TMP_SENS = 0u,
    CURR_SENS1,
    CURR_SENS2
}HW_AIN;

/**
* @brief Enumeration of hardware pieces that provide a digital input
* @implements	enum HW_DIN
*/
typedef enum
{
    INERFACE_BTN = 0u
}HW_DIN;
/*================================================================================================================
*									STRUCTURES AND OTHER TYPEDEFS
================================================================================================================*/
/**
* @brief Structure containing all data read from external hardware
* @implements	struct HW_DataCollection
*/
typedef struct
{
    uint16 current; // either from sensor1 or sensor2 based on user input
    uint16 temperature;
    //add more if needed
}HW_DataCollection;
/*================================================================================================================
*									GLOBAL VARIABLE DECLARATIONS
================================================================================================================*/

/*================================================================================================================
*									FUNCTION PROTOTYPES
================================================================================================================*/

/**
* @brief Reads analog value from an external sensor and converts it via ADC into uint16
 * @implements	HW_ReadSensor(HW_AIN sensor)
*/

uint16 HW_ReadSensor(HW_AIN sensor) {
    switch (sensor) {
        case CURR_SENS1:
            return HW_ReadCurrent1();
        case CURR_SENS2:
            return HW_ReadCurrent2();
        case TMP_SENS:
            return HW_ReadTemperature();
        default:
            return 0u;
    }
}

#endif /* HW_H */