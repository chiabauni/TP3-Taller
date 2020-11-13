#ifndef SERVER_COMMANDUNSUPPORTED_H
#define SERVER_COMMANDUNSUPPORTED_H
#include <string>
#include <sstream>
#include <mutex>
#include "server_command.h"
#include "server_lock.h"
//-------------------------------------------------------------------------------
class CommandUnsupported : public Command {
	std::mutex m;
	public:
		using Command::Command;
		std::string run() override;
};
#endif
