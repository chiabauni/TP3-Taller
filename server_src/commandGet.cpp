#include <sstream>
#include <string>
#include "../server_src/commandGet.h"
//-------------------------------------------------------------------------------
std::string CommandGet::run(){
	std::ostringstream stream;
	std::string resource = this->first_line.substr(0, 
											this->first_line.find(" "));
	if (this->root_posted == false) {
		this->dictionary.insertValueDictionary("root", this->root);
		this->root_posted = true;
	}
	if (this->first_line == " HTTP/1.1") {
		std::string root_text = this->dictionary.getValueDictionary("root");
		stream << response(GET_ROOT, root_text);
	} else {
		std::string resource_text = this->dictionary.getValueDictionary(
																	resource);
		if (resource_text == "NULL"){
			stream << response(GET_RESOURSE_FAIL);
		} else {
			stream << response(GET_RESOURSE_OK, resource_text);
		}
	}
	return stream.str();
}
