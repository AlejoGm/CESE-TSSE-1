#include "errores.h"
#include "leds.h"
#include "mock_errores.h"
#include "unity.h"
#include <stdint.h>

static uint16_t puerto_virtual;
void setUp() { LedsInitDriver(&puerto_virtual); }
void tearDown() {}

// - Después de la inicialización todos los LEDs deben quedar apagados. ✅
void test_al_iniciar_todos_los_leds_estan_apagados() {
  uint16_t puerto_virtual = 0xFFFF;
  LedsInitDriver(&puerto_virtual);
  TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// - Se puede prender un LED individual. ✅
void test_prender_un_led_invididual() {
  LedsTurnOn(3);
  TEST_ASSERT_EQUAL_HEX16(1 << 2, puerto_virtual);
}

// - Se puede apagar un LED individual. ✅
void test_apagar_un_led_invididual() {
  LedsTurnOn(3);
  LedsTurnOff(3);
  TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// - Se puede consultar el estado de un LED. ✅
void test_consultar_estado_leds() {
  LedsTurnOnAll();
  TEST_ASSERT_TRUE(LedsGetState(1));
  TEST_ASSERT_TRUE(LedsGetState(8));

  LedsTurnOff(8);
  TEST_ASSERT_FALSE(LedsGetState(8));
}

// - Se pueden prender y apagar múltiples LED’s. ✅
void test_prender_y_apagar_multiples_leds() {
  uint16_t mask = 0;
  LedsToMaskON(1, &mask);
  LedsToMaskON(3, &mask);
  LedsToMaskON(6, &mask);
  LedsToMaskON(12, &mask);
  LedsSet(mask);

  // TEST_ASSERT_EQUAL_HEX16((1 | 1 << 2 | 1 << 5 | 1 << 11), puerto_virtual);
  TEST_ASSERT_TRUE(LedsGetState(1));
  TEST_ASSERT_TRUE(LedsGetState(3));
  TEST_ASSERT_TRUE(LedsGetState(6));
  TEST_ASSERT_TRUE(LedsGetState(12));

  LedsToMaskOFF(3, &mask);
  LedsToMaskOFF(6, &mask);
  LedsSet(mask);

  // TEST_ASSERT_EQUAL_HEX16(1 | 1 << 11, puerto_virtual);
  TEST_ASSERT_TRUE(LedsGetState(1));
  TEST_ASSERT_FALSE(LedsGetState(3));
  TEST_ASSERT_FALSE(LedsGetState(6));
  TEST_ASSERT_TRUE(LedsGetState(12));
}

// - Se pueden prender todos los LEDs de una vez. ✅
void test_prender_todos_los_leds_de_una_vez() {
  LedsTurnOnAll();
  TEST_ASSERT_EQUAL_HEX16(0xFFFF, puerto_virtual);
}

// - Se pueden apagar todos los LEDs de una vez. ✅
void test_apagar_todos_los_leds_de_una_vez() {
  LedsTurnOnAll();
  LedsTurnOffAll();
  TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// Test realizados en clase

void test_prender_un_led_y_verificar_que_no_cambia_el_resto() {
  LedsTurnOn(3);
  TEST_ASSERT_EQUAL_HEX16(1 << 2, puerto_virtual);
}

void test_prender_un_led_cualquiera_y_apagarlo() {
  LedsTurnOn(5);
  LedsTurnOff(5);
  TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

void test_prender_mas_de_un_led_apagar_uno_y_verificar_que_el_resto_sigue_sin_cambios() {
  LedsTurnOn(3);
  LedsTurnOn(5);
  LedsTurnOff(3);
  TEST_ASSERT_EQUAL_HEX16(1 << 4, puerto_virtual);
}

void test_tratar_de_manipular_un_led_fuera_de_rango_y_comprobar_que_se_genere_un_error() {

  RegistrarMensaje_Expect(ALERTA, "IsLedValid", 0, "Intento de manipular un LED fuera de rango");
  RegistrarMensaje_IgnoreArg_linea();

  LedsTurnOn(0);
  TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

  RegistrarMensaje_ExpectAnyArgs();
  LedsTurnOn(17);
  TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}
