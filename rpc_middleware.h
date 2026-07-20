#ifndef RPC_MIDDLEWARE_H
#define RPC_MIDDLEWARE_H

#include <boost/asio.hpp>
#include <cstdint>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "Usuario.h"

namespace asio = boost::asio;
using asio::ip::tcp;

/**
 * @brief Escribe un entero de 32 bits en un vector de bytes en formato big-endian.
 * @param out Vector destino.
 * @param v Valor a escribir.
 */
void writeUint32(std::vector<char>& out, uint32_t v);

/**
 * @brief Lee un entero de 32 bits desde un vector de bytes.
 * @param in Vector origen.
 * @param pos Posición actual de lectura.
 * @return Valor leído.
 */
uint32_t readUint32(const std::vector<char>& in, size_t& pos);

/**
 * @brief Escribe una cadena precedida de su longitud.
 * @param out Vector destino.
 * @param s Cadena a escribir.
 */
void writeString(std::vector<char>& out, const std::string& s);

/**
 * @brief Lee una cadena precedida de su longitud.
 * @param in Vector origen.
 * @param pos Posición de lectura.
 * @return Cadena leída.
 */
std::string readString(const std::vector<char>& in, size_t& pos);

/**
 * @brief Comprueba las credenciales de un usuario de forma local.
 * @param usuarios Mapa de usuarios.
 * @param id ID del usuario.
 * @param pass Contraseña.
 * @return true si es válido.
 */
bool autenticarUsuarioLocal(std::map<int, Usuario*>& usuarios, int id, const std::string& pass);

/**
 * @brief Función cliente que realiza la llamada RPC de autenticación.
 *
 * Construye la petición con el formato:
 * | opcode(1 byte) | id(4 bytes) | lenPass(4 bytes) | password |
 *
 * Y espera una respuesta:
 * | status(1 byte) | result(1 byte) |
 *
 * @param sock Socket conectado.
 * @param id ID del usuario.
 * @param pass Contraseña.
 * @return true si el login es correcto.
 */
bool autenticarUsuarioRemoto(tcp::socket& sock, int id, const std::string& pass);

/**
 * @brief Procesa una petición RPC en el servidor.
 * @param req Petición recibida.
 * @param usuarios Mapa de usuarios.
 * @return Respuesta serializada.
 */
std::vector<char> procesarPeticionRPC(const std::vector<char>& req,
                                      std::map<int, Usuario*>& usuarios);

#endif