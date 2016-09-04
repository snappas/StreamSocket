//
// Created by ryan on 9/4/16.
//

#ifndef STREAMSOCKET_DATAMODEL_HXX
#define STREAMSOCKET_DATAMODEL_HXX

#include <map>
#include <string>
#include <vector>

class DataModel {
public:
    enum {
        GOOD_REQUEST = 1,
        BAD_REQUEST = 2
    };

    DataModel() {};

    std::string get(std::string key);

    void set(std::string key, std::string value);

    int parse_request(std::string *buffer);

    void parse_data(std::string buffer);

private:
    std::map<std::string, std::string> data;

    std::vector<std::string> tokenize(std::string buffer);
};


#endif //STREAMSOCKET_DATAMODEL_HXX
