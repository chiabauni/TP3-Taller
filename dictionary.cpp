#include "dictionary.h"
//------------------------------------------------------------------------------
DictionaryProtected::DictionaryProtected() {}

DictionaryProtected::~DictionaryProtected() {
	this->dic.clear();
}

std::string DictionaryProtected::getValueDictionary(std::string key){
	Lock l(m);
	std::map<std::string, std::string>::iterator it;
	it = this->dic.find(key);
	if (this->dic.find(key) != this->dic.end()){
		return (it->second);
	}
	return "NULL";
}
        
void DictionaryProtected::insertValueDictionary(std::string key, std::string value){
	Lock l(m);
	this->dic.insert(std::pair<std::string,std::string>(key, value));
}
