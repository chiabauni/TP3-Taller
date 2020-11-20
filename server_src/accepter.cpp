#include "../server_src/accepter.h"
#include "../common_src/socket.h"
//-------------------------------------------------------------------------------
void Accepter::_joinReaper() {
	std::list<ClientHandler *>::iterator it = client_list.begin();	
	while (it != client_list.end()){
		if (!(*it)->isRunning()) {
			(*it)->join();
			delete *it;
			it = client_list.erase(it);
		} else {
			++it;
		}
	}
}

void Accepter::_joinThreads() {
	std::list<ClientHandler *>::iterator it;
	for (it = client_list.begin(); it != client_list.end(); ++it) {
		(*it)->join();
		delete *it;
		it = client_list.erase(it);
	}
}

Accepter::Accepter(const char* service, std::string& root) : socket(service),
										root(root), keep_accepting(true) {}

Accepter::~Accepter() {}

void Accepter::run() {
	try {
		while (keep_accepting){
			try {
				Socket peer = socket.accept();
				ClientHandler *client = new ClientHandler(peer, root);
				client_list.push_back(client);
				client->start();
			} catch (const std::exception& e) {
				break;
			}
			_joinReaper();
		}
		_joinThreads();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

void Accepter::stop() {
	keep_accepting = false; 
	try{
		socket.shutdown();
		socket.close();
	} catch (const Exception& e) {
		std::cerr << "Error while shutingdown accepter: "<< e.what() 
														<< std::endl;
	}
}
