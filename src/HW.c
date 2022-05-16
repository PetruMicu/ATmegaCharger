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

/*================================================================================================================
*									GLOBAL VARIABLES
================================================================================================================*/

/*================================================================================================================
*									LOCAL FUNCTION PROTOTYPES
================================================================================================================*/

/*================================================================================================================
*									LOCAL FUNCTIONS
================================================================================================================*/
/**
* Reads current from sensor1 and converts it into uint16
*
*/
static uint16 HW_ReadCurrent1(void)
{
    uint16 result = 0u;
    return result;
}

/**
* Reads current from sensor2 and converts it into uint16
*
*/
static uint16 HW_ReadCurrent2(void)
{
    uint16 result = 0u;
    return result;
}

/**
* Reads temperature from temperature sensor and converts it into uint16
*
*/
static uint16 HW_ReadTemperature(void)
{
    ADMUX &= 0b11100001; // selects ADC0
    delay_us(10);
    ADCSRA |= (1u << ADSC); // starts conversion
    while(ADCSRA & (1<<ADIF) == 0)
    {
    } // wait until conversion finishes
    // disable interrupt flag
    ADCSRA |= (1u << ADIF);
    return ADCW;
}

static void HW_ADCInit(void)
{
    HW_REG8 copy;
    copy.reg8 = ADMUX;
    // Sets voltage reference to AVCC with external capacitor at AREF pin
    // Use right adjusted result
    // Select ADC0
    copy.reg8 = 0u;
    copy.bit6 = 1u;
    ADMUX = copy.reg8;
    ADCSRA = 0x83;// enable adc, no auto-trigger, no interrupts, prescaler x 8
}
/*================================================================================================================
*									GLOBAL FUNCTIONS
================================================================================================================*/

/**
* Modifies GPIO Registers in order to control
* the external devices
*
*/
void HW_Init(void)
{
    HW_REG8 copy;
    // A0,A1,A2 used as analog pins (disable digital buffers)
    DDRA = 0; // all inputs
    //DIDR0 = 0xFF; //disable all PORTA digital buffers to reduce power consumption
    // D2,D3 used as digital outputs (deactivated)
    // D7 used as digital input
    copy.reg8 = DDRD;
    copy.bit2 = 1u;
    copy.bit3 = 1u;
    copy.bit4 = 1u;
    copy.bit5 = 1u;
    DDRD = copy.reg8;
    copy.reg8 = PORTD;
    copy.bit2 = LVL_LOW;
    copy.bit2 = LVL_LOW;
    PORTD = copy.reg8;
    // test and modify if needed
    // B6, B7 used as digital outputs
    copy.reg8 = DDRB;
    copy.bit6 = 1u;
    copy.bit7 = 1u;
    DDRB = copy.reg8;
    copy.reg8 = PORTB;
    copy.bit6 = LVL_LOW;
    copy.bit7 = LVL_LOW;
    PORTB = copy.reg8;
    //ADC init
    HW_ADCInit();
}

/**
* Modifies GPIO value
*
*/
void HW_SetOutput(HW_OUT controlUnit, uint8 logicLevel)
{
    HW_REG8 copy;
    switch (controlUnit) {
        case GREED_LED:
            copy.reg8 = PORTD;
            copy.bit2 = logicLevel;
            PORTD = copy.reg8;
            break;
        case RED_LED:
            copy.reg8 = PORTD;
            copy.bit3 = logicLevel;
            PORTD = copy.reg8;
            break;
        case RELAY1:
            copy.reg8 = PORTB;
            copy.bit6 = logicLevel;
            PORTB = copy.reg8;
            break;
        case RELAY2:
            copy.reg8 = PORTB;
            copy.bit7 = logicLevel;
            PORTB = copy.reg8;
            break;
        default: // do nothing
    }

}

/**
* Reads digital input from devices like buttons
*
*/
uint8 HW_ReadInput(HW_DIN controlUnit)
{
    uint8 result;
    switch (controlUnit) {
        case INERFACE_BTN:
            result = (PORTD >> 7u) & 1u;
            break;
        default:
            result = LVL_LOW;
    }
    return result;
}

/**
* Calls local functions based on sensor
*
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

