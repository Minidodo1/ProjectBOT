//
// Created by Cedric on 02.09.2021.
//

#ifndef AOBOT_SLAVE_H
#define AOBOT_SLAVE_H
#include <sys/types.h>
#include <cstdint>
#include <aochat.h>
#include "lookup/server_packet.h"
#include "plugin.h"

//aocNameList* nameList;
struct log_info {const char *account, *password, *character;};

class Slave{
    aocConnection* aoc;
    aocEvent *event;
    struct sockaddr_in *addr;
    bool running = true;
public:
    void sendPacket(packet* packet);
    int connect(log_info *logInfo, Registry *r);
    void setRunning(bool status);
    bool getRunning() const;
    void sendPrivateMessage(int char_id, std::string *msg, bool add_color=true);
};
char *GetCharName(uint32_t uid);
#endif //AOBOT_SLAVE_H
