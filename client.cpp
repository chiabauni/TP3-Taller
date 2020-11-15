#include "client.h"
#define BUFF_SIZE 64
//-------------------------------------------------------------------------------
Client::Client(const char* host, const char* service) : socket(host, service){}

Client::~Client(){} 

void Client::run() {
	std::string line;
	while (std::getline(std::cin, line)){
		line += '\n';
		socket.send(line.data(), line.length());
	}
	//fprintf(stderr, "[DEBUG] Shuting down writing channel for client...\n");
	socket.shutdown(SHUT_WR);
	//fprintf(stderr, "[DEBUG] Client's writing channel shutdown.\n");
	std::stringstream stream;
	int status = 1;
	int bytes_received = 0;
	char buffer [BUFF_SIZE];
	//fprintf(stderr, "[DEBUG] Client receiving message...\n");
	while (status != 0){
		status = socket.receive(buffer, BUFF_SIZE, bytes_received);
		for(int i = 0; i < bytes_received; i++) {
			stream << buffer[i];
		}
	}
	//fprintf(stderr, "[DEBUG] Message received.\n");
	std::string message = stream.str();
	std::cout << message;
}
