#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H
#include <bits/unique_ptr.h>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include "../server_src/dictionary.h"
//-------------------------------------------------------------------------------
class Command {
	protected:
		std::string& first_line;
		std::string& text;
		std::string& root;
		DictionaryProtected dictionary;
		bool root_posted;
		static const char GET_ROOT[];
		static const char GET_RESOURSE_OK[];
		static const char GET_RESOURSE_FAIL[];
		static const char POST_ROOT[];
		static const char POST_RESOURSE[];
		static const char OTHER_METHOD[];
	
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
		static std::string response(const char* message,
									const std::string& body);
		static std::string response(const char* message);
		virtual std::string run() = 0;
};
#endif
