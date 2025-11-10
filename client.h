#ifndef MEDIUS_CLIENT_H
#define MEDIUS_CLIENT_H


#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
using SOCKET = int;
#endif


#include <string>
#include <thread>
#include <atomic>


class Client {
public:
	Client(const std::string& server_ip, int port);
	~Client();


	bool connectToServer();
	void run();


private:
	std::string server_ip_;
	int port_;
	SOCKET client_socket_;
	std::atomic<bool> running_;


	void receiveMessages();
};


#endif