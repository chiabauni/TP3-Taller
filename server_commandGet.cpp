#include <sstream>
#include <string>
#include "server_commandGet.h"
//-------------------------------------------------------------------------------
std::string CommandGet::run(){
	Lock l(m);
	std::ostringstream stream;
	std::map<std::string, std::string>::iterator it;
	std::string resource = this->first_line.substr(0, 
											this->first_line.find(" "));
	if (this->root_posted == false) {
		this->dic.insert(std::pair<std::string,std::string>("root",
															this->root));
		this->root_posted = true;
	}
	if (this->first_line == " HTTP/1.1") {
		it = this->dic.find("root");
		std::string root_text = (it->second);
		stream << response(GET_ROOT, root_text);
	} else if (this->dic.find(resource) != this->dic.end()) {
		it = this->dic.find(resource);
		std::string resource_text = (it->second);
		stream << response(GET_RESOURSE_OK, resource_text);
	} else {
		stream << response(GET_RESOURSE_FAIL);
	}
	return stream.str();
}
