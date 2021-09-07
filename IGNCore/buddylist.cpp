//
// Created by Cedric on 07.09.2021.
//

#include <iostream>
#include "buddylist.h"
#include "plugin.h"
#include "lookup/server_packet.h"
#include <functional>
BuddyListService* bls;
BuddyListService* getBLS() { return bls;}

void addBuddy(packet *p){ bls->addBuddyByPacket(p);}
void inject(Registry* reg) {
    auto a([](packet* p){ bls->addBuddyByPacket(p);});
    reg->getEventService()->registerPacketHandler(10, reinterpret_cast<phandler *>(&a));

}

void pre_start() {

}


void start() {

}


BuddyListService::BuddyListService(Registry* r) {
    this->buddymap.reserve(2048);
    std::function<void(packet*)> f = std::bind(&BuddyListService::addBuddyByPacket, this, std::placeholders::_1);
    std::cout << "Test" << std::endl;
    r->getEventService()->registerPacketHandler(ServerPacket::BUDDY_STATUS, &f);
}
bool BuddyListService::addBuddy(const int char_id, const char* type) {
    return false;
}
buddy* BuddyListService::getBuddy(const int char_id) {
    auto user = buddymap.find(char_id);
    if (user->second == nullptr) return nullptr;
    return user->second;
}
bool BuddyListService::remBuddy(const int char_id) {
    auto* buddy = getBuddy(char_id);
    if (buddy == nullptr) return false;
    std::unordered_set<std::string> map = buddy->types;
    map.clear();
    delete buddy;
    return true;
}

void BuddyListService::addBuddyByPacket(packet *p) {
    auto data = (BuddyStatus* )p->data;
    if(!buddymap.contains(data->char_id)){
        using namespace std;
        buddymap.insert({data->char_id, new buddy{data->char_id,
                                                  unordered_set<string>{},
                                                  false,
                                                  0, p->owner}});
    }
}

void BuddyListService::remBuddy(packet *p) {
    auto data = (BuddyRemoved*)p->data;
    auto* buddy = getBuddy(data->char_id);
    if (buddy == nullptr) return;
    std::unordered_set<std::string> map = buddy->types;
    map.clear();
    delete buddy;
}


