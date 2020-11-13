#include "server_commandPost.h"
//-------------------------------------------------------------------------------
std::string CommandPost::run(){
	Lock l(m);
	std::ostringstream stream;
	std::map<std::string, std::string>::iterator it;
	if (this->first_line == " HTTP/1.1") {
		stream << response(POST_ROOT);
	} else {
		std::string resource = this->first_line.substr(0,
												this->first_line.find(" "));
		this->dic.insert(std::pair<std::string,std::string>(resource,
															this->text));
		std::string resource_text = (this->text);
		stream << response(POST_RESOURSE, resource_text);
	}
	return stream.str();
}
