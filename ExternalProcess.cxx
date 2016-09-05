//
// Created by ryan on 9/4/16.
//

#include <stdio.h>
#include "ExternalProcess.hxx"

ExternalProcess::ExternalProcess(std::string command):command(command) {


}

ExternalProcess &ExternalProcess::start_process() {
    pipe = popen(command.c_str(), "r");
    return *this;
}

int ExternalProcess::get_descriptor() {
    if(!pipe){
        return -1;
    }else {
        return fileno(pipe);
    }
}
