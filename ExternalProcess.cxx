//
// Created by ryan on 9/4/16.
//

#include <stdio.h>
#include "ExternalProcess.hxx"

ExternalProcess::ExternalProcess(std::string command):command(command) {


}

int ExternalProcess::getFileDescriptor() {
    FILE* pipe = popen(command.c_str(), "r");
    if(!pipe){
        return -1;
    }else {
        return fileno(pipe);
    }
}
