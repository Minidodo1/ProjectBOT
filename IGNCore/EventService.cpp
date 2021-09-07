//
// Created by Cedric on 07.09.2021.
//

#include "EventService.h"
#include <unordered_map>
void EventService::registerPacketHandler(int packet_id, phandler* function) {
    std::vector<phandler> packet_handlers;
    if (!packetMap.contains(packet_id)) {
        auto map = new std::vector<phandler>;
        packetMap.insert({packet_id, *map});
    }
    packet_handlers = packetMap.find(packet_id)->second;
    packet_handlers.push_back(*function);
    packetMap.insert_or_assign(packet_id, packet_handlers);

}

bool EventService::callPacketHandlers(packet* p) {
    if (!packetMap.contains(p->type)) return false;
    for (const auto &item: packetMap) {
        for (const auto &item2: item.second)
            item2(p);

    }
    return true;
}
