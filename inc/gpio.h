
#ifndef GPIO_H
#define GPIO_H

/** @file gpio.h
 ** @brief Definición de la función principal del programa
 **/

/* === Headers files inclusions
 * ================================================================ */

#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++
 * ============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions
 * =============================================================== */

/* === Public data type declarations
 * =========================================================== */

/**
 * @brief Punteroa estructura que representa un GPIO
 */
typedef struct gpio_s *gpio_t;

/* === Public variable declarations
 * ============================================================ */

/* === Public function declarations
 * ============================================================ */

/**
 * @brief Crea una nueva instancia de un objeto GPIO
 *
 * @param port puerto del GPIO
 * @param bit bit del GPIO
 * @return gpio_t puntero a la instancia del GPIO creada
 */
gpio_t gpioCreate(uint8_t port, uint8_t bit);

/**
 * @brief Configura el GPIO como salida o entrada
 *
 * @param gpio instancia del GPIO
 * @param output true si es salida, false si es entrada
 */
void gpioSetOutput(gpio_t gpio, bool output);

/**
 * @brief Configura el estado del GPIO
 *
 * @param gpio instancia del GPIO
 * @param state true para alto, false para bajo
 */
void gpioSetState(gpio_t gpio, bool state);

/**
 * @brief Obtiene el estado del GPIO
 *
 * @param gpio instancia del GPIO
 * @return true si el GPIO está en alto, false si está en bajo
 */
bool gpioGetState(gpio_t gpio);

/* === End of documentation
 * ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H */
