#include "server.h"
#include "client.h"
#include <iostream>
#include "logger.h"

#define VERSION "1.0"

int main(int argc, char* argv[]) {

	std::string banner = R"( 
 _           _           _  _  _  _  _           _  _  _  _              _  _  _           _            _             _  _  _  _     
(_) _     _ (_)         (_)(_)(_)(_)(_)         (_)(_)(_)(_)            (_)(_)(_)         (_)          (_)          _(_)(_)(_)(_)_   
(_)(_)   (_)(_)         (_)                      (_)      (_)_             (_)            (_)          (_)         (_)          (_)  
(_) (_)_(_) (_)         (_) _  _                 (_)        (_)            (_)            (_)          (_)         (_)_  _  _  _     
(_)   (_)   (_)         (_)(_)(_)                (_)        (_)            (_)            (_)          (_)           (_)(_)(_)(_)_   
(_)         (_)         (_)                      (_)       _(_)            (_)            (_)          (_)          _           (_)  
(_)         (_)         (_) _  _  _  _           (_)_  _  (_)            _ (_) _          (_)_  _  _  _(_)         (_)_  _  _  _(_)  
(_)         (_)         (_)(_)(_)(_)(_)         (_)(_)(_)(_)            (_)(_)(_)           (_)(_)(_)(_)             (_)(_)(_)(_)    
    
	                                                                                                                                    )";
	log(INFO) << banner << std::endl;
	log(INFO) << "Welcome to Medius connector. Starting Medius..." << std::endl;
	if ((argc < 3)||(argv[1] == nullptr)) {
		std::cout << "Usage:\n";
		std::cout << "To start server: medius server <port>\n";
		std::cout << "To start client: medius client <ip> <port>\n";
		log(INFO) << "executed without arguements. Exiting..." << std::endl;
		return 0;
	}

	std::string mode = argv[1];



	if (mode == "--server" || mode == "-s") {
		int port = std::stoi(argv[2]);
		Server server(port);
		if (server.start()) server.run();
	}
	else if (mode=="--version" || mode=="-v") {
		std::cout << "Medius Version " << VERSION << std::endl;
		return 0;
	}
	else if (mode == "--client" || mode=="-c") {
		if (argc < 4) {
			log(WARNING) << "Error: Client mode requires IP and port." << std::endl;
			return 1;
		}
		std::string ip = argv[2];
		int port = std::stoi(argv[3]);
		Client client(ip, port);
		if (client.connectToServer()) client.run();
	}
	else {
		std::cout << "Unknown mode. Use 'server' or 'client'. Try `Medius.exe --help`" << std::endl;
		return 0;
	}
	return 0;
}