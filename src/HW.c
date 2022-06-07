/*================================================================================================================
* Project: AtmegaCharger
* Platform: AvrStudio4
* MCU: ATmega164A
* Subject: Project2 (P2)
* Owners: Petru Micu, Andreea-Ioana Andrei
* Professor: Adrian Paun
================================================================================================================*/
#include "../include/HW.h"
#include <mega164a.h>
#include <alcd_twi.h>
uint8_t powerRelay = 0; // off
uint8_t batteryRelay = 0; // 0 LiPo, 1 NiMH

static uint16_t readAdc(uint8_t adcInput)
{
    ADMUX=adcInput | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
    delay_us(10);
// Start the AD conversion
    ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
    while ((ADCSRA & (1<<ADIF))==0);
    ADCSRA|=(1<<ADIF);
    return ADCW;
}

static void HW_ADCInit(void)
{
    HW_REG8 copy;
    copy.reg8 = ADMUX;
    copy.reg8 = 0u; // Sets voltage reference to AVCC with external capacitor at AREF pin
    copy.bit6 = 1u; // Use right adjusted result
    ADMUX = copy.reg8;
    ADCSRA = 0x83;// enable adc, no auto-trigger, no interrupts, prescaler x 8
}

/**
* Modifies GPIO Registers in order to control
* the external devices
*/
void HW_Init(void)
{
    HW_REG8 copy;
    DDRA = 0; // all analog inputs
    DIDR0 = 0xFF; //disable all PORTA digital buffers to reduce power consumption
    copy.reg8 = DDRD;
    copy.bit2 = 1u; //PORTD2 -> GREEN LED
    copy.bit3 = 1u; //PORTD3 -> RED LED
    copy.bit5 = 0u; //PORTD5 -> BUTTON INTERFACE
    copy.bit6 = 1u; //PORTD6 -> ON-OFF LED
    copy.bit7 = 0u; //PORTD7 -> DIGITAL_TMP SENSOR
    DDRD = copy.reg8;
    copy.reg8 = PORTD;
    copy.bit2 = 1u;
    copy.bit3 = 1u;
    copy.bit5 = 1u;
    PORTD = copy.reg8;
    // test and modify if needed
    // B6, B7 used as digital outputs
    copy.reg8 = DDRB;
    copy.bit6 = 1u; // PORTB6 -> ON-OFF RELAY
    copy.bit7 = 1u; // PORTB7 -> ROUTE RELAY
    DDRB = copy.reg8;
    copy.reg8 = PORTB;
    copy.bit6 = LVL_LOW;
    copy.bit7 = LVL_LOW;
    PORTB = copy.reg8;
    // C7 input
    PORTC |= (1u << PORTC7);
    //ADC init
    HW_ADCInit();
    //Enable PCINT3 interrupt for PCINT29 <-> PD5
    PCICR |= (1u << PCIE3) | (1 << PCIE2);
    PCMSK3 |= (1u << PCINT29);
    PCMSK2 |= (1u << PCINT23);
}

/**
* Modifies GPIO value
*/
void HW_SetOutput(HW_OUT controlUnit, uint8 logicLevel)
{
    HW_REG8 copy;
    switch (controlUnit)
    {
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
        case POWER_RELAY:
            copy.reg8 = PORTB;
            copy.bit6 = logicLevel;
            PORTB = copy.reg8;
            copy.reg8 = PORTD;
            copy.bit6 = !logicLevel;
            PORTD = copy.reg8;
            break;
        case BATTERY_RELAY:
            copy.reg8 = PORTB;
            copy.bit7 = logicLevel;
            PORTB = copy.reg8;
            break;
        default: // do nothing
    }

}

/**
* Reads digital input from devices like buttons
*/
uint8 HW_ReadInput(HW_DIN controlUnit)
{
    uint8 result;
    switch (controlUnit)
    {
        case INTERFACE_BTN:
            result = (PORTD >> 5u) & 1u;
        case DIGITAL_TMP_SENSOR:
            result = (PORTD >> 7u) & 1u;
        default:
            result = LVL_LOW;
    }
    return !result;
}

/**
* Calls local functions based on sensor
*/
uint16 HW_ReadSensor(HW_AIN sensor)
{
    switch (sensor)
    {
        case CURR_SENS:
            return readAdc(CURR_SENS); // adc1
        case TMP_SENS:
            return readAdc(TMP_SENS); // adc0
        default:
            return 0u;
    }
}
void LCD_init()
{
    twi_master_init(100);
    lcd_twi_init(0x27,16);
}

/**
* Shows the first interface when the button is pressed.
*
*/
/*void LCD_interface1()
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
*/

interrupt [PC_INT2] void BATTERY(void)
{
    if(((PINC >> 7u) & 1u) == 0)
    {
        batteryRelay ^= 1u;
        if(batteryRelay == 1) //
            HW_SetOutput(BATTERY_RELAY,LVL_HIGH);
        else
            HW_SetOutput(BATTERY_RELAY,LVL_LOW);
        delay_ms(700);
    }
}

interrupt [PC_INT3] void POWER(void)
{
    if(((PIND >> 5u) & 1u) == 0)
    {
        powerRelay ^= 1u;
        if(powerRelay == 1)
            HW_SetOutput(POWER_RELAY,LVL_HIGH);
        else
            HW_SetOutput(POWER_RELAY,LVL_LOW);
        delay_ms(700);
    }
}

