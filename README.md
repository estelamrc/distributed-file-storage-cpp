# Distributed File Storage System

Distributed client-server system developed in C++ for remote user and file management using an RPC-based architecture.

## Overview

This project implements a distributed file storage application composed of a client, a server and an RPC middleware layer. It supports user administration, file management and asynchronous notifications.

## Features

- Client-server architecture
- Remote procedure calls through a custom RPC middleware
- User and administrator management
- Text and image file handling
- User storage quota control
- Notification queue
- Modular object-oriented design
- Compilation using Make

## Technologies

- C++
- RPC
- Client-server architecture
- Object-oriented programming
- Make
- Linux

## Project structure
```text
.
├── tele_client.cpp
├── tele_server.cpp
├── rpc_middleware.cpp
├── Administrador.cpp
├── Cliente.cpp
├── Usuario.cpp
├── Fichero.cpp
├── FicheroTexto.cpp
├── FicheroImagen.cpp
├── Notification.cpp
├── NotificationQueue.cpp
└── Makefile

## Build

Compile the project using:
make

## Execution

Start the server:

./tele_server

Start the client in another terminal:

./tele_client

### Author
Estela Rodríguez
