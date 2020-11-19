#ifndef SERVER_COMMANDGET_H
#define SERVER_COMMANDGET_H
#include <string>
#include <sstream>
#include <mutex>
#include "../server_src/command.h"
//-------------------------------------------------------------------------------
class CommandGet : public Command {
	public:
		using Command::Command;
		std::string run() override;
};
#endif
