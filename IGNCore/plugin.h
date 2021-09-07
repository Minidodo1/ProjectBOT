//
// Created by Cedric on 05.09.2021.
//

#ifndef AOBOT_PLUGIN_H
#define AOBOT_PLUGIN_H

#include "EventService.h"
#include "buddylist.h"
#include "lookup/LookupService.h"
class Registry{
    class BuddyListService* bls;
    class EventService* es;
    class CommandService* cs;
    class LookupService* ls;
public:
    LookupService* getLookupService();
    EventService* getEventService();
    BuddyListService* getBuddyListService();
    CommandService* getCommandService();
    void setBuddyList(BuddyListService* param);
    void setEventService(EventService* param);
    void setCommandService(CommandService* param);
    void setLookupService(LookupService* param);

};
struct API{
    void (*const inject)(Registry*);
    void (*const pre_start)();
    void (*const start)();
    void (*const register_events)();
};
extern "C" {
    void inject(Registry* r);
    void pre_start();
    void start();
//    API load(){
//        API a = API{&inject, &pre_start, &start};
//        return a;
//    }
};
#endif //AOBOT_PLUGIN_H
