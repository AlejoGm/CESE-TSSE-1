#include "leds.h"
#include "errores.h"

#include <stdbool.h>
#include <stdint.h>

#define ALL_LED_OFF 0x0000
#define ALL_LED_ON 0xFFFF
#define LED_TO_BIT_OFFSET 1
#define FIRST_BIT 1
#define LED_MIN 1
#define LED_MAX 16

static uint16_t *puerto;

static uint16_t s_LedToMask(int led) { return FIRST_BIT << (led - LED_TO_BIT_OFFSET); }

static bool IsLedValid(int led) {
  if (led < LED_MIN || led > LED_MAX) {
    Alerta("Intento de manipular un LED fuera de rango");
    return false;
  }
  return true;
}

static void s_validateAndON(int led, uint16_t *ptr) {
  if (!ptr || !IsLedValid(led)) {
    return;
  }
  *ptr |= s_LedToMask(led);
}

static void s_validateAndOFF(int led, uint16_t *ptr) {
  if (!ptr || !IsLedValid(led)) {
    return;
  }
  *ptr &= ~s_LedToMask(led);
}

void LedsInitDriver(uint16_t *puerto_virtual) {
  puerto = puerto_virtual;
  LedsTurnOffAll();
}

void LedsTurnOn(int led) { s_validateAndON(led, puerto); }
void LedsTurnOff(int led) { s_validateAndOFF(led, puerto); }

bool LedsGetState(int led) { return (*puerto & s_LedToMask(led)) > 0; }

void LedsToMaskON(int led, uint16_t *mask) { s_validateAndON(led, mask); }
void LedsToMaskOFF(int led, uint16_t *mask) { s_validateAndOFF(led, mask); }
void LedsSet(uint16_t mask) { *puerto = mask; }

void LedsTurnOnAll() { *puerto = ALL_LED_ON; }
void LedsTurnOffAll() { *puerto = ALL_LED_OFF; }
