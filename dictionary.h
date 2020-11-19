#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <mutex>
#include <map>
#include <string>
#include "server_lock.h"
//------------------------------------------------------------------------------
class DictionaryProtected {
    private:
        std::mutex m;        

        std::map<std::string,std::string> dic;
    public: 
    	/* Constructor */
       DictionaryProtected();

        /* Destructor */
        ~DictionaryProtected();

        std::string getValueDictionary(std::string key);
        
        void insertValueDictionary(std::string key, std::string value);
};
#endif
