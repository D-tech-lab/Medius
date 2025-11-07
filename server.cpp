#include "server.h"
#include "logger.h"
#include <iostream>
using namespace std;
Server::Server(int port) : port_(port), server_socket_(INVALID_SOCKET), max_sd_(0) {
    FD_ZERO(&master_set_);
}

Server::~Server() {
    stop();
}

bool Server::initialize() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return false;
    }
#endif
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_ == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        return false;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_);

    if (bind(server_socket_, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed." << std::endl;
        closesocket(server_socket_);
        return false;
    }

    if (listen(server_socket_, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed." << std::endl;
        closesocket(server_socket_);
        return false;
    }

    FD_SET(server_socket_, &master_set_);
    max_sd_ = server_socket_;

    log(INFO)<< "Server initialized on port " << port_ << std::endl;
    return true;
}

bool Server::start() {
    return initialize();
}

void Server::acceptNewClient() {
    sockaddr_in client_addr{};
    socklen_t addrlen = sizeof(client_addr);
    SOCKET new_socket = accept(server_socket_, (struct sockaddr*)&client_addr, &addrlen);

    if (new_socket != INVALID_SOCKET) {
        clients_.push_back(new_socket);
        FD_SET(new_socket, &master_set_);
        if (new_socket > max_sd_) max_sd_ = new_socket;

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        log(INFO)<< "New client connected: " << client_ip << std::endl;
    }
}

void Server::broadcastMessage(const std::string& message, SOCKET sender) {
    for (SOCKET client : clients_) {
        if (client != sender) {
            send(client, message.c_str(), static_cast<int>(message.size()), 0);
        }
    }
}

void Server::handleClientMessages() {
    fd_set read_fds = master_set_;
    int activity = select(static_cast<int>(max_sd_ + 1), &read_fds, nullptr, nullptr, nullptr);

    if (activity < 0) {
        std::cerr << "select() error" << std::endl;
        return;
    }

    // Handle new connections
    if (FD_ISSET(server_socket_, &read_fds)) {
        acceptNewClient();
    }

    // Handle messages
    for (auto it = clients_.begin(); it != clients_.end();) {
        SOCKET client_socket = *it;
        if (FD_ISSET(client_socket, &read_fds)) {
            char buffer[1024] = { 0 };
            int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

            if (bytes_received <= 0) {
                log(INFO)<< "Client disconnected." << endl;
                closesocket(client_socket);
                FD_CLR(client_socket, &master_set_);
                it = clients_.erase(it);
                continue;
            }
            else {
                buffer[bytes_received] = '\\0';
                std::string message = buffer;
                log(INFO)<< "Broadcasting: " << message << endl;
                    broadcastMessage(message, client_socket);
            }
        }
        ++it;
    }
}

void Server::run() {
    log(INFO)<< "Server running..." << endl;
        while (true) {
            handleClientMessages();
        }
}

void Server::stop() {
    for (SOCKET client : clients_) closesocket(client);
    if (server_socket_ != INVALID_SOCKET) closesocket(server_socket_);
#ifdef _WIN32
    WSACleanup();
#endif
    log(INFO)<< "Server stopped." << endl;
}
