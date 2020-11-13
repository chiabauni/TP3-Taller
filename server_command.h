#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H
#include <bits/unique_ptr.h>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
//-------------------------------------------------------------------------------
class Command {
	protected:
		std::string& first_line;
		std::string& text;
		std::string& root;
		bool root_posted;
		std::map<std::string,std::string> dic;
		static const std::string GET_ROOT;
		static const std::string GET_RESOURSE_OK;
		static const std::string GET_RESOURSE_FAIL;
		static const std::string POST_ROOT;
		static const std::string POST_RESOURSE;
		static const std::string OTHER_METHOD;
	public:
		explicit Command(std::string& first_line, std::string& text);
		explicit Command(std::string& first_line,
						std::string& text,
						std::string& root);
		~Command();
		static std::unique_ptr<Command> getCommand(std::string& instruction,
													std::string& first_line,
													std::string& text,
													std::string& root);
		static std::string response(const std::string message,
									std::string& body);
		static std::string response(const std::string message);
		virtual std::string run() = 0;
};
#endif
