//
// Created by Cedric on 07.09.2021.
//

#ifndef AOBOT_BUDDYLIST_H
#define AOBOT_BUDDYLIST_H

#include <unordered_map>
#include <unordered_set>
#include "packet.h"
class Registry;
struct buddy{
    int char_id;
    std::unordered_set<std::string> types;
    bool online;
    int status;
    int slave_id;

};
class BuddyListService {
    std::unordered_map<int, buddy*> buddymap{};
public:
    explicit BuddyListService(Registry *r);
    bool addBuddy(int char_id, const char* type);
    bool remBuddy(int character);
    //buddy* getBuddy(const char *character);
    buddy* getBuddy(int character);
    void addBuddyByPacket(packet* p);
    void remBuddy(packet* p);
};
char *nameLowerCase(const char *str);
#endif //AOBOT_BUDDYLIST_H
