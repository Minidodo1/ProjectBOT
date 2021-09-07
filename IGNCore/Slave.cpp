//
// Created by Cedric on 02.09.2021.
//

#include <iostream>
#include "Slave.h"


void Slave::sendPacket(packet *packet) {}
int Slave::connect(log_info *logInfo, Registry *r) {
    this->addr = aocMakeAddr("chat.d1.funcom.com", 7105);
    int user_id;
    this->aoc = aocInit(nullptr);
    this->aoc = aocInit(this->aoc);
    if (!aocConnect(this->aoc, this->addr)) {
        std::cout << "Fatal socket error for slave " << logInfo->character << std::endl;
        return 2;
    }
    //auto* bls = new BuddyListService;
    aocTimerNew(this->aoc, 1, 60, 0, nullptr);
    while (this->running) {
        aocPollVarArg(60, 0, 1, this->aoc);

        /* Process events */
        while ((event = aocEventGet())) {
            switch (event->type) {
                case AOC_EVENT_CONNECT: {
                    printf("%s >> Connected to chat server!\n", logInfo->character);
                    break;
                }
                case AOC_EVENT_CONNFAIL:
                    std::cout << " >> Connection failed. \n" << (int *) event->data << std::endl;
                    this->running = false;
                    break;

                case AOC_EVENT_DISCONNECT:
                    std::cout << ">> Disconnected from chat server. \n" << (int *) event->data << std::endl;
                    running = false;
                    break;

                case AOC_EVENT_MESSAGE: {
                    packet* p = getPacket((aocMessage *) event->data, user_id);
                    switch(p->type){
                        case (ServerPacket::LOGIN_SEED):{
                            auto* ls = (LoginSeed*) p->data;
                            auto* key = aocKeyexGenerateKey(ls->key, logInfo->account, logInfo->password);
                            aocSendLoginResponse(this->aoc, 0, logInfo->account, key);
                            break;
                        }
                        case (ServerPacket::LOGIN_CHARLIST):{
                            auto* lcl = (LoginCharacterList*) p->data;
                            std::string b (character);

                            for (const auto &item : lcl->characters){
                                std::string a (item.char_name);
                                if (a == logInfo->character){
                                    aocSendLoginSelectChar(this->aoc, item.user_id);
                                    user_id = item.user_id;
                                    std::cout << ">> SELECTED: "<<item.char_name <<std::endl;
                                }
                            }
                            break;
                        }

                        case(ServerPacket::PONG):{
                            auto* pong = (Pong*) p->data;
                            printf("Received Pong: %s < %s\n", logInfo->character, pong->blob);
                            break;
                        }
                        case (ServerPacket::BUDDY_STATUS):{
                            auto* bs = (BuddyStatus*) p->data;

                            std::string name = r->getLookupService()->getName(bs->char_id);

                            if (name.empty()) name = bs->char_id;
                            if(bs->online)
                                std::cout << (bs->online ? "[ONLINE] " : "[OFFLINE] ") <<
                                             (bs->status ? "Permanent" : "Temporary") <<
                                             " buddy " << name << std::endl;
                            r->getEventService()->callPacketHandlers(p);
                            r->getBuddyListService()->addBuddyByPacket(p);
                            break;
                        }
                        case (ServerPacket::CLIENT_NAME):{
                            auto* cn = (CharacterName*) p->data;
                            r->getLookupService()->updateNameResolver(cn->char_id, cn->name);
                            break;
                        }
                        case (ServerPacket::SYSTEM_MESSAGE):{
                            break;
                        }
                    }

                    delPacket(p);

                    break;

                }

                case AOC_EVENT_TIMER: {
                    if (((aocTimer *) event->data)->id == 1) {
                        printf("Sending Ping: %s > %s\n", logInfo->character, logInfo->character);
                        aocSendPing(this->aoc, (unsigned char *) (logInfo->character), -1);
                    }
                    break;
                }
            }

            /* Destroy the event */
            aocEventDestroy(event);
        }
    }
    aocDisconnect(this->aoc);
    aocFree(this->aoc);
    running = false;
    return 0;
}

void Slave::setRunning(bool status) {
    running = status;
}

bool Slave::getRunning() const{
    return running;
}
void Slave::sendPrivateMessage(int char_id, std::string *msg, bool add_color) {
    aocSendPrivateMessage(this->aoc, char_id, msg->data(), msg->size(), nullptr, 0);
}
