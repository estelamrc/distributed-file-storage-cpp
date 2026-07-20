#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <thread>
#include <vector>

#include "rpc_middleware.h"
#include "Usuario.h"
#include "Administrador.h"
#include "Cliente.h"
#include "Fichero.h"
#include "FicheroTexto.h"
#include "FicheroImagen.h"
#include "Notification.h"
#include "NotificationQueue.h"

namespace asio = boost::asio;
using asio::ip::tcp;

std::map<int, Usuario*> mapaUsuarios;

void consumerLoop(NotificationQueue& cola) {
    std::ofstream log("eventos.log", std::ios::app);

    while (true) {
        Notification n = cola.pop();
        log << n.display() << std::endl;
        log.flush();
    }
}

void enviarMensaje(tcp::socket& sock, std::string texto) {
    if (texto.empty() || texto[texto.size() - 1] != '\n') {
        texto += "\n";
    }
    asio::write(sock, asio::buffer(texto));
}

std::string recibirMensaje(tcp::socket& sock, asio::streambuf& buf) {
    asio::read_until(sock, buf, '\n');
    std::istream is(&buf);
    std::string linea;
    std::getline(is, linea);
    return linea;
}

std::string listarFicherosUsuario(Usuario* usuario) {
    std::ostringstream salida;
    const std::map<std::string, Fichero*>& ficheros = usuario->getMisFicheros();

    if (ficheros.empty()) {
        return "No tienes ficheros";
    }

    salida << "Ficheros del usuario " << usuario->getNombre() << ":";

    for (std::map<std::string, Fichero*>::const_iterator it = ficheros.begin();
         it != ficheros.end(); ++it) {
        salida << "\n- " << it->second->getNombre()
               << " (tamano: " << it->second->getTamano() << ")";
    }

    return salida.str();
}

bool leerPeticionLogin(tcp::socket& sock, std::vector<char>& req) {
    req.clear();

    std::vector<char> cabecera(9);
    asio::read(sock, asio::buffer(cabecera));

    size_t pos = 1;
    readUint32(cabecera, pos);
    uint32_t passLen = readUint32(cabecera, pos);

    req.insert(req.end(), cabecera.begin(), cabecera.end());

    if (passLen > 0) {
        std::vector<char> pass(passLen);
        asio::read(sock, asio::buffer(pass));
        req.insert(req.end(), pass.begin(), pass.end());
    }

    return true;
}

int obtenerIdDePeticionLogin(const std::vector<char>& req) {
    size_t pos = 1;
    return static_cast<int>(readUint32(req, pos));
}

void manejarSesionUsuario(tcp::socket& sock,
                          asio::streambuf& buf,
                          Usuario* usuarioLogueado,
                          NotificationQueue& cola) {
    while (true) {
        enviarMensaje(sock, "\nMenu:");
        enviarMensaje(sock, "1. Ver mis datos");
        enviarMensaje(sock, "2. Listar ficheros");
        enviarMensaje(sock, "3. Anadir fichero");
        enviarMensaje(sock, "0. Salir");
        enviarMensaje(sock, "--INPUT--Opcion");

        std::string opcionStr = recibirMensaje(sock, buf);
        int opcion = std::stoi(opcionStr);

        if (opcion == 1) {
            enviarMensaje(sock, usuarioLogueado->mostrarInformacion());
        } else if (opcion == 2) {
            cola.push(Notification("FILES_LISTED", usuarioLogueado->getNombre(), ""));
            enviarMensaje(sock, listarFicherosUsuario(usuarioLogueado));
        } else if (opcion == 3) {
            enviarMensaje(sock, "--INPUT--Nombre del fichero");
            std::string nombre = recibirMensaje(sock, buf);

            enviarMensaje(sock, "--INPUT--Contenido");
            std::string contenido = recibirMensaje(sock, buf);

            enviarMensaje(sock, "--INPUT--Tipo (1=Texto, 2=Imagen)");
            int tipo = std::stoi(recibirMensaje(sock, buf));

            bool ok = false;

            try {
                ok = usuarioLogueado->addFichero(nombre, contenido, tipo);
            } catch (...) {
                ok = false;
            }

            if (ok) {
                cola.push(Notification("UPLOAD_COMPLETED",
                                       usuarioLogueado->getNombre(),
                                       nombre));
                enviarMensaje(sock, "Fichero anadido correctamente");
            } else {
                cola.push(Notification("UPLOAD_FAILED",
                                       usuarioLogueado->getNombre(),
                                       nombre));
                enviarMensaje(sock, "Error al anadir fichero");
            }
        } else if (opcion == 0) {
            cola.push(Notification("LOGOUT", usuarioLogueado->getNombre(), ""));
            enviarMensaje(sock, "Sesion cerrada");
            enviarMensaje(sock, "--EXIT--");
            return;
        } else {
            enviarMensaje(sock, "Opcion invalida");
        }
    }
}

int main() {
    try {
        NotificationQueue cola;
        std::thread worker(consumerLoop, std::ref(cola));
        worker.detach();

        mapaUsuarios[1] = new Administrador(1, "admin", "admin");
        mapaUsuarios[2] = new Cliente(2, "user", "user");

        asio::io_context io;
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 9090));

        std::cout << "[SERVER] Esperando conexiones en el puerto 9090..." << std::endl;

        while (true) {
            tcp::socket sock(io);
            acceptor.accept(sock);

            std::cout << "[SERVER] Cliente conectado." << std::endl;

            std::vector<char> req;
            leerPeticionLogin(sock, req);

            int id = obtenerIdDePeticionLogin(req);

            std::vector<char> resp = procesarPeticionRPC(req, mapaUsuarios);
            asio::write(sock, asio::buffer(resp));

            bool loginOk = resp.size() >= 2 && resp[0] == 0 && resp[1] == 1;

            if (!loginOk) {
                cola.push(Notification("LOGIN_FAIL", std::to_string(id), ""));
                std::cout << "[SERVER] Login incorrecto para ID " << id << std::endl;
                continue;
            }

            Usuario* usuarioLogueado = mapaUsuarios[id];

            cola.push(Notification("LOGIN_OK", usuarioLogueado->getNombre(), ""));

            std::cout << "[SERVER] Login correcto para "
                      << usuarioLogueado->getNombre() << std::endl;

            asio::streambuf buf;
            manejarSesionUsuario(sock, buf, usuarioLogueado, cola);
        }

    } catch (const std::exception& e) {
        std::cerr << "[SERVER] Error: " << e.what() << std::endl;
    }

    for (std::map<int, Usuario*>::iterator it = mapaUsuarios.begin();
         it != mapaUsuarios.end(); ++it) {
        delete it->second;
    }

    return 0;
}                                                      