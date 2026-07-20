#include "rpc_middleware.h"

void writeUint32(std::vector<char>& out, uint32_t v) {
    out.push_back(static_cast<char>((v >> 24) & 0xFF));
    out.push_back(static_cast<char>((v >> 16) & 0xFF));
    out.push_back(static_cast<char>((v >> 8) & 0xFF));
    out.push_back(static_cast<char>(v & 0xFF));
}

uint32_t readUint32(const std::vector<char>& in, size_t& pos) {
    if (pos + 4 > in.size()) {
        throw std::runtime_error("No hay suficientes bytes para leer uint32");
    }

    uint32_t v = 0;
    v |= (static_cast<uint32_t>(static_cast<unsigned char>(in[pos])) << 24);
    v |= (static_cast<uint32_t>(static_cast<unsigned char>(in[pos + 1])) << 16);
    v |= (static_cast<uint32_t>(static_cast<unsigned char>(in[pos + 2])) << 8);
    v |= static_cast<uint32_t>(static_cast<unsigned char>(in[pos + 3]));
    pos += 4;
    return v;
}

void writeString(std::vector<char>& out, const std::string& s) {
    writeUint32(out, static_cast<uint32_t>(s.size()));
    out.insert(out.end(), s.begin(), s.end());
}

std::string readString(const std::vector<char>& in, size_t& pos) {
    uint32_t len = readUint32(in, pos);

    if (pos + len > in.size()) {
        throw std::runtime_error("Longitud de string invalida");
    }

    std::string s(in.begin() + pos, in.begin() + pos + len);
    pos += len;
    return s;
}

bool autenticarUsuarioLocal(std::map<int, Usuario*>& usuarios, int id, const std::string& pass) {
    std::map<int, Usuario*>::iterator it = usuarios.find(id);

    if (it == usuarios.end() || it->second == NULL) {
        return false;
    }

    return it->second->getPassword() == pass;
}

bool autenticarUsuarioRemoto(tcp::socket& sock, int id, const std::string& pass) {
    std::vector<char> req;
    req.push_back(1);
    writeUint32(req, static_cast<uint32_t>(id));
    writeString(req, pass);

    asio::write(sock, asio::buffer(req));

    std::vector<char> resp(2);
    asio::read(sock, asio::buffer(resp));

    unsigned char status = static_cast<unsigned char>(resp[0]);
    unsigned char result = static_cast<unsigned char>(resp[1]);

    if (status != 0) {
        return false;
    }

    return result == 1;
}

std::vector<char> procesarPeticionRPC(const std::vector<char>& req,
                                      std::map<int, Usuario*>& usuarios) {
    std::vector<char> resp;

    try {
        if (req.size() < 9) {
            throw std::runtime_error("Peticion demasiado corta");
        }

        size_t pos = 0;
        unsigned char opcode = static_cast<unsigned char>(req[pos]);
        pos++;

        if (opcode != 1) {
            throw std::runtime_error("Opcode no soportado");
        }

        int id = static_cast<int>(readUint32(req, pos));
        std::string pass = readString(req, pos);

        bool ok = autenticarUsuarioLocal(usuarios, id, pass);

        resp.push_back(0);
        resp.push_back(ok ? 1 : 0);
    } catch (...) {
        resp.push_back(1);
        resp.push_back(0);
    }

    return resp;
}