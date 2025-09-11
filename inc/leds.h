
#include <stdbool.h>
#include <stdint.h>

void LedsInitDriver(uint16_t *puerto_virtual);
void LedsTurnOn(int led);
void LedsTurnOff(int led);
void LedsTurnOnAll();
void LedsTurnOffAll();
void LedsToMaskON(int led, uint16_t *mask);
void LedsToMaskOFF(int led, uint16_t *mask);
void LedsSet(uint16_t mask);
bool LedsGetState(int led);
