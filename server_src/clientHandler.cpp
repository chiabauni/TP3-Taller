#include "../server_src/clientHandler.h"
#include "../server_src/command.h"
//-------------------------------------------------------------------------------
ClientHandler::ClientHandler(Socket& socket, std::string& root) : 
						peer(std::move(socket)), root(root), is_running(true) {}

ClientHandler::~ClientHandler() {}

bool ClientHandler::isRunning() const {
	return is_running;
}

void ClientHandler::run() {
	while(is_running) {
		std::stringstream stream;
		int status = 1;
		int bytes_received = 0;
		char buffer [BUFF_SIZE];
		while (status != 0){
			try {
				status = peer.receive(buffer, BUFF_SIZE, bytes_received);
			} catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
			for(int i = 0; i < bytes_received; i++) {
				stream << buffer[i];
			}
		}
		std::string message = processRequest(stream);
		try {
			peer.send(message.c_str(), message.length());
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		peer.shutdown(SHUT_WR);
		is_running = false;
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
