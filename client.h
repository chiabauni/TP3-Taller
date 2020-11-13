#ifndef CLIENT_H
#define CLIENT_H
#include "common_socket.h"
#include <iostream>
#include <string>
#include <sstream>
//-------------------------------------------------------------------------------
class Client{
	Socket socket;

	public:
		Client(const char* host, const char* service);
		~Client();

		Client(const Client&) = delete;
		Client& operator=(const Client&) = delete;
		Client(Client&& other) = delete;
		Client& operator=(Client&& other) = delete;	

		void run();
};
#endif
