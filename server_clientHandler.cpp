#include "server_clientHandler.h"
#include "server_command.h"
//-------------------------------------------------------------------------------
ClientHandler::ClientHandler(Socket& socket, std::string& root) : 
						peer(std::move(socket)), root(root), is_running(true) {}

ClientHandler::~ClientHandler() {}

bool ClientHandler::isRunning() const {
	return is_running;
}

void ClientHandler::run() {
	try {
		while(is_running) {
				std::stringstream stream;
				int status = 1;
				int bytes_received = 0;
				char buffer [BUFF_SIZE];
				while (status != 0){
					status = peer.receive(buffer, BUFF_SIZE, bytes_received);
					for(int i = 0; i < bytes_received; i++) {
						stream << buffer[i];
					}
				}
				std::string message = processRequest(stream);
				peer.send(message.c_str(), message.length());
				is_running =false;
		}
	} catch (const std::exception& e) {
		fprintf(stderr, "%s\n", e.what());
	}
}

void ClientHandler::stop() {
	try {
		peer.shutdown();
		peer.close();
	} catch (const Exception& e){
		fprintf(stderr,"Error while shutdown of peer.\n");
	}
}

std::string ClientHandler::processRequest(std::stringstream& stream) {
	std::string instruction;
	std::string first_line;
	std::string line;
	std::getline(stream, instruction, '/');
	std::getline(stream, first_line);
	bool text_reached = false;
	std::stringstream text;
	while (std::getline(stream, line)){
		if(line == "") text_reached = true;
		if(text_reached) {
			line += '\n';
			text << line;
		}
	}
	std::string body = text.str();
	return runCommand(instruction, first_line, body);
}
std::string ClientHandler::runCommand(std::string& instruction,
										std::string& first_line,
										std::string& text){
	std::unique_ptr<Command> command = Command::getCommand(instruction,
															first_line,
															text,
															root);
	return command->run();
}
