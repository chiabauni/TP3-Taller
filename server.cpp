#include "server.h" 
//-------------------------------------------------------------------------------
Server::Server(const char* service, std::string& root) : 
												accepter(service, root) {}

Server::~Server() {}

void Server::run() {
	//fprintf(stderr, "[DEBUG] Starting Server::run.\n");
	accepter.start();
	char input;
	do {
		input = std::getchar();
	} while(input != 'q');
	//fprintf(stderr, "[DEBUG] Q received, stopping accepter...\n");
	accepter.stop();
	//fprintf(stderr, "[DEBUG] Accepter stopped. Joining accepter...\n");
	accepter.join();
	//fprintf(stderr, "[DEBUG] Accepter joined. Ending Server::run.\n");
}
