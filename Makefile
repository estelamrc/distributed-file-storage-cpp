CXX = g++
CXXFLAGS = -Wall -g -std=c++17
LIBS = -lboost_system -pthread

SERVER = tele_rpc_server
CLIENT = tele_rpc_client

SERVER_OBJS = tele_server.o rpc_middleware.o Usuario.o Administrador.o Cliente.o Fichero.o FicheroTexto.o FicheroImagen.o Notification.o NotificationQueue.o
CLIENT_OBJS = tele_client.o rpc_middleware.o Usuario.o Administrador.o Cliente.o Fichero.o FicheroTexto.o FicheroImagen.o

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) $(SERVER_OBJS) -o $(SERVER) $(LIBS)

$(CLIENT): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJS) -o $(CLIENT) $(LIBS)

tele_server.o: tele_server.cpp Usuario.h Administrador.h Cliente.h Fichero.h FicheroTexto.h FicheroImagen.h CuotaExcedidaException.h rpc_middleware.h Notification.h NotificationQueue.h
	$(CXX) $(CXXFLAGS) -c tele_server.cpp

tele_client.o: tele_client.cpp rpc_middleware.h
	$(CXX) $(CXXFLAGS) -c tele_client.cpp

rpc_middleware.o: rpc_middleware.cpp rpc_middleware.h Usuario.h
	$(CXX) $(CXXFLAGS) -c rpc_middleware.cpp

Usuario.o: Usuario.cpp Usuario.h Fichero.h FicheroTexto.h FicheroImagen.h CuotaExcedidaException.h
	$(CXX) $(CXXFLAGS) -c Usuario.cpp

Administrador.o: Administrador.cpp Administrador.h Usuario.h
	$(CXX) $(CXXFLAGS) -c Administrador.cpp

Cliente.o: Cliente.cpp Cliente.h Usuario.h
	$(CXX) $(CXXFLAGS) -c Cliente.cpp

Fichero.o: Fichero.cpp Fichero.h
	$(CXX) $(CXXFLAGS) -c Fichero.cpp

FicheroTexto.o: FicheroTexto.cpp FicheroTexto.h Fichero.h CuotaExcedidaException.h
	$(CXX) $(CXXFLAGS) -c FicheroTexto.cpp

FicheroImagen.o: FicheroImagen.cpp FicheroImagen.h Fichero.h CuotaExcedidaException.h
	$(CXX) $(CXXFLAGS) -c FicheroImagen.cpp

Notification.o: Notification.cpp Notification.h
	$(CXX) $(CXXFLAGS) -c Notification.cpp

NotificationQueue.o: NotificationQueue.cpp NotificationQueue.h Notification.h
	$(CXX) $(CXXFLAGS) -c NotificationQueue.cpp

clean:
	rm -f *.o $(SERVER) $(CLIENT) eventos.log