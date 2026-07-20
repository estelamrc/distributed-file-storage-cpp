#include <boost/asio.hpp>
#include <iostream>
#include <limits>
#include <string>

#include "rpc_middleware.h"

namespace asio = boost::asio;
using asio::ip::tcp;

void enviarMensaje(tcp::socket& sock, std::string texto) {
    if (texto.empty() || texto[texto.size() - 1] != '\n') {
        texto += "\n";
    }
    asio::write(sock, asio::buffer(texto));
}

std::string recibirDeRed(tcp::socket& sock, asio::streambuf& buf) {
    asio::read_until(sock, buf, '\n');
    std::istream is(&buf);
    std::string linea;
    std::getline(is, linea);
    return linea;
}

int main() {
    try {
        asio::io_context io;
        tcp::socket sock(io);

        sock.connect(tcp::endpoint(asio::ip::make_address("127.0.0.1"), 9090));
        std::cout << "[CLIENT] Conectado al servidor.\n";

        int id;
        std::string pass;

        std::cout << "ID> ";
        std::cin >> id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Password> ";
        std::getline(std::cin, pass);

        bool ok = autenticarUsuarioRemoto(sock, id, pass);

        if (!ok) {
            std::cout << "Login incorrecto\n";
            return 0;
        }

        std::cout << "Login correcto\n";

        asio::streambuf buf;

        while (true) {
            try {
                std::string msg = recibirDeRed(sock, buf);

                if (msg.size() >= 9 && msg.substr(0, 9) == "--INPUT--") {
                    std::cout << msg.substr(9) << "> ";
                    std::string teclado;
                    std::getline(std::cin, teclado);
                    enviarMensaje(sock, teclado);
                } else if (msg == "--EXIT--") {
                    break;
                } else {
                    std::cout << msg << std::endl;
                }

            } catch (const boost::system::system_error& e) {
                if (e.code() == asio::error::eof) {
                    std::cout << "[CLIENT] El servidor ha cerrado la conexion.\n";
                    break;
                }
                throw;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "[CLIENT] Error: " << e.what() << "\n";
    }

    return 0;
}