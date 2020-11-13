#include "server_accepter.h"
//-------------------------------------------------------------------------------
void Accepter::_acceptClient() {
	Socket peer = socket.accept();
	client_list.emplace_back(peer, root);
	client_list.back().start();
}

void Accepter::_joinReaper() {
	for (auto it = client_list.begin(); it != client_list.end();) {
		if (!(it->isRunning())) {
			it->stop();
			it->join();
			it = client_list.erase(it);
		} else {
			it++;
		}
	}
}

void Accepter::_joinThreads() {
	for (auto it = client_list.begin(); it != client_list.end();) {
		it->stop();
		it->join();
		it = client_list.erase(it);
	}
}

Accepter::Accepter(const char* service, std::string& root) : socket(service),
										root(root), keep_accepting(true) {}

Accepter::~Accepter() {
	try{
		_joinThreads();
	} catch (const std::exception& e) {
		fprintf(stderr, "%s\n", e.what());
	}
}

void Accepter::run() {
	try{
		while (keep_accepting) {
			_acceptClient();
			_joinReaper();
		}
	} catch (const std::exception& e) {
		fprintf(stderr, "%s\n", e.what());
	}
	_joinThreads();
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
