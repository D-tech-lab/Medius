#include<iostream>
#include "logger.h"
#include "server.h"
using namespace std;
int main() {
	log(INFO) << "Application started." << endl;
    Server server(8080);

    if (!server.start()) {
        log(WARNING) << "Failed to start server." << endl;
        return 1;
    }

    server.run();
	log(INFO) << "Application finished." << endl;
	return 0;
}