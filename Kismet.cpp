#include "Kismet.h"
#include "Prompt.h"

int Kismet::parse(std::istream& istream) {
    std::string line;
    int status = 0;
    while(!status && std::getline(istream,line)) {
        status = parseline(line);
    }
    return 0;
}

int Kismet::parse() {
    std::string line;
    int status = 0;
    while(!status && !_prompt.eof()) {
        line = _prompt.readline();
        if(line.empty()) {
            if(_lastline.size())
                status = parseline(_lastline);
        } else {
            if(line == "exit")
                return -1;
            status = parseline(line);
            _lastline = line;
        }
    }
    return 0;
}

int Kismet::parseline(const std::string& line) {

    std::cout << std::endl;
    

    return 0;
}