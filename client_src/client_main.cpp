#include "../client_src/client.h"
//-------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
	if (argc != 3){
		std::cerr << "Error invalid arguments" <<std::endl;
		return 1;
	}
	char* host = argv[1];
	char* service = argv[2];
	try {
		Client client(host, service);
		client.run();
	} catch (const Exception& e){
		std::cerr << e.what() << std::endl;
		return 2;
	} catch (...) {
		std::cerr << "Unknown error" << std::endl;
		return 3;
	}
	return 0;
}
