#include "server.h" 
//-------------------------------------------------------------------------------
Server::Server(const char* service, std::string& root) : 
												accepter(service, root) {}

Server::~Server() {}

void Server::run() {
	accepter.start();
	char input;
	do {
		input = std::getchar();
	} while(input != 'q');
	accepter.stop();
	accepter.join();
}
