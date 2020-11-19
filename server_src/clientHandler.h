#ifndef SERVER_CLIENTHANDLER_H
#define SERVER_CLIENTHANDLER_H
#define BUFF_SIZE 64
#include <atomic>
#include <vector>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include "../server_src/thread.h"
#include "../common_src/socket.h"
//-------------------------------------------------------------------------------
class ClientHandler : public Thread {
	Socket peer;
	std::string& root;
	std::atomic<bool> is_running;
	std::string result;
	std::string processRequest(std::stringstream& stream);
	std::string runCommand(std::string& instruction, 
							std::string& first_line,
							std::string& text);

	public:
		explicit ClientHandler(Socket& socket, std::string& root);
		~ClientHandler();

		ClientHandler(const ClientHandler&) = delete;
		ClientHandler operator=(const ClientHandler&) = delete;
		ClientHandler(ClientHandler&& other) = delete;
		ClientHandler operator=(ClientHandler&& other) = delete;

		bool isRunning() const;
		void run() override;
};
#endif
