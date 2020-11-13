#include "server_command.h"
#include "server_commandGet.h"
#include "server_commandPost.h"
#include "server_commandUnsupported.h"
#include <sstream>
#include <string>
//-------------------------------------------------------------------------------
const std::string Command::GET_ROOT = 
							"HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
const std::string Command::GET_RESOURSE_OK = "HTTP/1.1 200 OK\n\n";
const std::string Command::GET_RESOURSE_FAIL = "HTTP/1.1 404 NOT FOUND\n\n";
const std::string Command::POST_ROOT = "HTTP/1.1 403 FORBIDDEN\n\n";
const std::string Command::POST_RESOURSE = "HTTP/1.1 200 OK\n\n";
const std::string Command::OTHER_METHOD = 
							"HTTP/1.1 405 METHOD NOT ALLOWED\n\n";

Command::Command(std::string& first_line, std::string& text) : 
							first_line(first_line), text(text), root(text) {}
Command::Command(std::string& first_line,
				std::string& text,
				std::string& root) : first_line(first_line), 
								text(text), root(root), root_posted(false){}

Command::~Command(){}

std::unique_ptr<Command> Command::getCommand(std::string& instruction,
											std::string& first_line,
											std::string& text,
											std::string& root) {
	std::ostringstream stream;
	if (instruction == "GET ") {
		stream << instruction << "/" << first_line << "\n";
		std::cout << stream.str();
		return std::unique_ptr<Command>(new CommandGet(first_line, text,
														root));
	} else if(instruction == "POST "){
		stream << instruction << "/" << first_line << "\n";
		std::cout << stream.str();
		return std::unique_ptr<Command>(new CommandPost(first_line, text));
	} else {
		return std::unique_ptr<Command>(new CommandUnsupported(instruction,
																text));
	}
}

std::string Command::response(const std::string message, std::string& body){
	std::ostringstream stream;
	stream << message << body;
	return stream.str();
}

std::string Command::response(const std::string message){
	return message;
}
