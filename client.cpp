#include "client.h"
#include <iostream>
#include "logger.h"

Client::Client(const std::string& server_ip, int port)
	: server_ip_(server_ip), port_(port), client_socket_(INVALID_SOCKET), running_(true) {
}


Client::~Client() {
	running_ = false;
	if (client_socket_ != INVALID_SOCKET) closesocket(client_socket_);
#ifdef _WIN32
	WSACleanup();
#endif
}


bool Client::connectToServer() {
#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		log(WARNING) << "WSAStartup failed." << std::endl;
		return false;
	}
#endif


	client_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket_ == INVALID_SOCKET) {
		log(WARNING) << "Socket creation failed." << std::endl;
		return false;
	}


	sockaddr_in server_addr{};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_);


	if (inet_pton(AF_INET, server_ip_.c_str(), &server_addr.sin_addr) <= 0) {
		log(WARNING) << "Invalid address/ Address not supported." << std::endl;
		return false;
	}


	if (connect(client_socket_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		log(WARNING) << "Connection to server failed." << std::endl;
		return false;
	}


	log(INFO) << "Connected to server at " << server_ip_ << ":" << port_ << std::endl;
	return true;
}


void Client::receiveMessages() {
	char buffer[2048];

	while (running_) {
		int bytes_received = recv(client_socket_, buffer, sizeof(buffer) - 1, 0);

		if (bytes_received > 0) {
			buffer[bytes_received] = '\0';

			std::cout << "\n" << buffer << std::endl;
			std::cout << ">> " << std::flush;
		}
		else if (bytes_received == 0) {
			std::cout << "\nDisconnected from server." << std::endl;
			running_ = false;
			break;
		}
	}
}



void Client::run() {
	std::thread recv_thread(&Client::receiveMessages, this);
	recv_thread.detach(); // ✅ keep listening in background

	std::string input;
	while (running_) {
		std::cout << ">> ";
		std::getline(std::cin, input);

		if (input == "exit" || input == "quit") {
			running_ = false;
			break;
		}

		send(client_socket_, input.c_str(), static_cast<int>(input.size()), 0);
	}

	closesocket(client_socket_);
}
