#ifndef SERVER_COMMANDPOST_H
#define SERVER_COMMANDPOST_H
#include <string>
#include <sstream>
#include <mutex>
#include "server_command.h"
#include "server_lock.h"
//-------------------------------------------------------------------------------
class CommandPost : public Command {
	std::mutex m;
	public:
		using Command::Command;
		std::string run() override;
};
#endif
