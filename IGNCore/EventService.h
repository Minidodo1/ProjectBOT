//
// Created by Cedric on 07.09.2021.
//

#ifndef PROJECTBOT_EVENTSERVICE_H
#define PROJECTBOT_EVENTSERVICE_H


#include <unordered_map>
#include <unordered_set>
#include "functional"
#include "packet.h"
#include <vector>
typedef std::function<void(packet*)> phandler;
class EventService {

    std::unordered_map<int, std::vector<phandler>> packetMap;
public:
    void registerPacketHandler(int packet_id, phandler* function);
    bool callPacketHandlers(packet* p);
};


#endif //PROJECTBOT_EVENTSERVICE_H
