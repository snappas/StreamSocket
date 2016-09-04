//
// Created by ryan on 9/4/16.
//
#include <sstream>
#include <iostream>
#include <vector>
#include "DataModel.hxx"

void DataModel::set(std::string key, std::string value) {
    data[key] = value;
}

std::string DataModel::get(std::string key) {
    std::string value;
    try {
        value = data.at(key);
    } catch (std::out_of_range) {
        value = "null";
    }
    return value + std::string("\n");
}

int DataModel::parse_request(std::string *buffer) {
    std::vector<std::string> argv = tokenize(*buffer);
    if (!argv.empty() && argv[0].compare("get") == 0 && argv.size() > 1) {
        *buffer = get(argv[1]);
        return GOOD_REQUEST;
    } else {
        return BAD_REQUEST;
    }
}

void DataModel::parse_data(std::string buffer) {
    std::vector<std::string> tokens = tokenize(buffer);
    if (!tokens.empty()) {
        set("temperature", tokens[0]);
    }
}

std::vector<std::string> DataModel::tokenize(std::string buffer) {
    std::vector<std::string> argv;
    std::string arg;
    std::stringstream ss(buffer);
    while (ss >> arg) {
        argv.push_back(arg);
    }
    return argv;
}
