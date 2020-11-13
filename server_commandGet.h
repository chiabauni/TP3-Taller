#ifndef SERVER_COMMANDGET_H
#define SERVER_COMMANDGET_H
#include <string>
#include <sstream>
#include <mutex>
#include "server_command.h"
#include "server_lock.h"
//-------------------------------------------------------------------------------
class CommandGet : public Command {
	std::mutex m;
	public:
		using Command::Command;
		std::string run() override;
};
#endif
