//
// Created by Cedric on 07.09.2021.
//

#include <iostream>
#include "LookupService.h"

void LookupService::updateNameResolver(int char_id, const std::string *char_name) {
    const std::lock_guard<std::mutex> lock(write_lock);
    // For random cleanup-prevention, we'll copy the username into the cache, instead of linking it.
    id2name.insert_or_assign(char_id, *char_name);
    name2id.insert_or_assign(*char_name, char_id);
}
void LookupService::updateNameResolver(int char_id, const char* char_name){
    std::string s(char_name);
    this->updateNameResolver(char_id, &s);
}

/*
 * Since int's are as large as pointers,
 * we can just return a copy of the char_id
 */
int LookupService::getCharID(const char *char_name) {
    auto user = name2id.find(char_name);
    if(!user->first.empty()){
        return user->second;
    }
    return -1;
}
/*
 * We'll return a reference to the actual name,
 * its the users purpose to create a copy of it if desired.
 */
std::string LookupService::getName(int char_id) {

    auto user = id2name.find(char_id);
    if(user != nullptr){
        return user->second;
    }
    return "";
}