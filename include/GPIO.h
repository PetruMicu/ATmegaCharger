/*================================================================================================================
* Project: AtmegaCharger
* Platform: AvrStudio4
* MCU: ATmega164A
* Subject: Project2 (P2)
* Owners: Petru Micu, Andreea-Ioana Andrei
* Professor: Adrian Paun
================================================================================================================*/
#include "PrimitiveTypeDefs.h"
#include <stdint.h>
#include <mega164A.h>

#ifndef GPIO_H
#define GPIO_H

#define HIGH 1u
#define LOW 0u
#define OUT 1u


void pinMode(char PORT, uint8_t PIN, uint8_t DIRECTION);
void setLevel(char PORT, uint8_t PIN, uint8_t LEVEL);

#endif /* GPIO_H */