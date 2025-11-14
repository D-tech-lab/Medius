#ifndef MEDIUS_SERVER_H
#define MEDIUS_SERVER_H

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
using SOCKET = int;
#endif
#include <vector>
#include <string>
#include <unordered_map>

class Server {
public:
    explicit Server(int port);
    ~Server();
    std::unordered_map<SOCKET, std::string> client_ips;
    bool start();
    void run();
    void stop();

private:
    int port_;
    SOCKET server_socket_;
    fd_set master_set_;
    SOCKET max_sd_;
    std::vector<SOCKET> clients_;

    bool initialize();
    void acceptNewClient();
    void handleClientMessages();
    void broadcastMessage(const std::string& message, SOCKET sender);
};

#endif // MEDIUS_SERVER_H
