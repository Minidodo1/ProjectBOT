//
// Created by Cedric on 07.09.2021.
//

#ifndef PROJECTBOT_LOOKUPSERVICE_H
#define PROJECTBOT_LOOKUPSERVICE_H

#include "string"
#include "unordered_map"
#include "mutex"
class LookupService {
    std::mutex write_lock;
    std::unordered_map<int, std::string> id2name;
    std::unordered_map<std::string, int> name2id;

public:
    std::string getName(int char_id);
    int getCharID(const char* char_name);

    void updateNameResolver(int char_id, const std::string* char_name);
    void updateNameResolver(int char_id, const char* char_name);
};


#endif //PROJECTBOT_LOOKUPSERVICE_H
