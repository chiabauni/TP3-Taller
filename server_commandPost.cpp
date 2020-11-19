#include "server_commandPost.h"
//-------------------------------------------------------------------------------
std::string CommandPost::run(){
	std::ostringstream stream;
	if (this->first_line == " HTTP/1.1") {
		stream << response(POST_ROOT);
	} else {
		std::string resource = this->first_line.substr(0,
												this->first_line.find(" "));
		this->dictionary.insertValueDictionary(resource, this->text);
		std::string resource_text = (this->text);
		stream << response(POST_RESOURSE, resource_text);
	}
	return stream.str();
}
