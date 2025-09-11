#ifndef ERRORES_H
#define ERRORES_H

typedef enum gravedad_e {
  ERROR,       //!< Mensaje de error
  ALERTA,      //!< Mensaje de alerta
  INFORMACION, //!< Mensaje de informacion
  DEPURACION,  //!< Mensaje de depuracino
} gravedad_t;

#define Alerta(mensaje) RegistrarMensaje(ALERTA, __FUNCTION__, __LINE__, mensaje)

/**
 * @brief Funcion para registrar un mensaje en la bitacora de errores del sistema
 * @param gravedad Nivel de gravedad del mensaje registrado
 * @param funcion Funcion que realiza el registro del mensaje
 * @param Linea Linea del codigo fuente en la que se llama al registro del mensaje
 * @param mensaje Cadena de caracteres con el mensaje que se desea registrar void
 */
void RegistrarMensaje(gravedad_t gravedad, const char *funcion, int linea, const char *mensaje);

#endif
