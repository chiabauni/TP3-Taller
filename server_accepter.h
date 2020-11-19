#ifndef SERVER_ACCEPTER_H
#define SERVER_ACCEPTER_H
#include <list>
#include <atomic>
#include "common_socket.h"
#include "server_thread.h"
#include "server_clientHandler.h"
//-------------------------------------------------------------------------------
class Accepter: public Thread {
	Socket socket;
	std::string& root;
	std::atomic<bool> keep_accepting;
	std::list<ClientHandler *> client_list;

	void _joinReaper();
	void _joinThreads();

	public:
		explicit Accepter(const char* service, std::string& root);
		~Accepter();
		
		Accepter(const Accepter&) = delete;
		Accepter operator=(const Accepter&) = delete;
		Accepter(Accepter&& other) = delete;
		Accepter operator=(Accepter&& other) = delete;

		void run() override;
		void stop();
};
#endif
