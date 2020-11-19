#ifndef SERVER_COMMANDPOST_H
#define SERVER_COMMANDPOST_H
#include <string>
#include <sstream>
#include <mutex>
#include "../server_src/command.h"
//-------------------------------------------------------------------------------
class CommandPost : public Command {
	public:
		using Command::Command;
		std::string run() override;
};
#endif
