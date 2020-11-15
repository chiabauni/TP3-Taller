#include "server_accepter.h"
#include "common_socket.h"
//-------------------------------------------------------------------------------
/*void Accepter::_acceptClient() {
	Socket peer = socket.accept();
	client_list.emplace_back(peer, root);
	client_list.back().start();
}*/

void Accepter::_joinReaper() {
	std::list<ClientHandler>::iterator it = client_list.begin();
	//fprintf(stderr, "[DEBUG] _joinReaper started.\n");	
	while (it != client_list.end()){
		if (!(it->isRunning())) {
			//fprintf(stderr, "[DEBUG] One reaper to join.\n");
			it->stop();
			it->join();
			it = client_list.erase(it);
		} else {
			it++;
		}
	}
	//fprintf(stderr, "[DEBUG] _joinReaper finished.\n");
}

void Accepter::_joinThreads() {
	//fprintf(stderr, "[DEBUG] _joinThreads started.\n");
	for (auto it = client_list.begin(); it != client_list.end();) {
		//fprintf(stderr, "[DEBUG] One thread to join.\n");
		it->stop();
		it->join();
		it = client_list.erase(it);
	}
	//fprintf(stderr, "[DEBUG] _joinThreads finished.\n");
}

Accepter::Accepter(const char* service, std::string& root) : socket(service),
										root(root), keep_accepting(true) {}

Accepter::~Accepter() {}

void Accepter::run() {
	try{
		//fprintf(stderr, "[DEBUG] Starting accepter.\n");
		while (keep_accepting){
			try {
				//fprintf(stderr, "[DEBUG] Accepter waiting for a client...\n");
				Socket peer = socket.accept();
				//fprintf(stderr, "[DEBUG] Client accepted!\n");
				client_list.emplace_back(peer, root);
				client_list.back().start();
			} catch (const std::exception& e) {
				fprintf(stderr, "[DEBUG] Exception in accepter.\n");
				break;
			}
			//fprintf(stderr, "[DEBUG] Joining reaper/s...\n");
			_joinReaper();
			//fprintf(stderr, "[DEBUG] Reaper/s joined.\n");
		}
		//fprintf(stderr, "[DEBUG] Accepter joining threads...\n");
		_joinThreads();
		//fprintf(stderr, "[DEBUG] Threads joined. Ending accepter.\n");
	} catch (const std::exception& e) {
		fprintf(stderr, "%s\n", e.what());
	}
}

void Accepter::stop() {
	keep_accepting = false; 
	try{
		socket.shutdown();
		socket.close();
	} catch (const Exception& e) {
		fprintf(stderr, "Error while shutdown of accepter.\n");
	}
}
