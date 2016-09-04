//
// Created by ryan on 9/4/16.
//

#ifndef STREAMSOCKET_EXTERNALPROCESS_HXX
#define STREAMSOCKET_EXTERNALPROCESS_HXX
#include <string>

class ExternalProcess {
public:
    ExternalProcess(std::string command);
    int getFileDescriptor();
private:
    std::string command;
};


#endif //STREAMSOCKET_EXTERNALPROCESS_HXX
