#include "server_commandUnsupported.h"
//-------------------------------------------------------------------------------
std::string CommandUnsupported::run(){
	Lock l(m);
	std::ostringstream stream;
	std::string message = "es un comando desconocido";
	stream << response(OTHER_METHOD) << first_line << message << "\n" ;
	return stream.str();
}