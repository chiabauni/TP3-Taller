#ifndef SERVER_COMMANDUNSUPPORTED_H
#define SERVER_COMMANDUNSUPPORTED_H
#include <string>
#include <sstream>
#include <mutex>
#include "server_command.h"
//-------------------------------------------------------------------------------
class CommandUnsupported : public Command {
	public:
		using Command::Command;
		std::string run() override;
};
#endif
