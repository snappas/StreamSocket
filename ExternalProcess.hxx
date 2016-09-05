//
// Created by ryan on 9/4/16.
//

#ifndef STREAMSOCKET_EXTERNALPROCESS_HXX
#define STREAMSOCKET_EXTERNALPROCESS_HXX
#include <string>

class ExternalProcess {
public:
    ExternalProcess(std::string command);

    ExternalProcess &start_process();

    int get_descriptor();
private:
    std::string command;
    FILE *pipe;
};


#endif //STREAMSOCKET_EXTERNALPROCESS_HXX
