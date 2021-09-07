//
// Created by Cedric on 31.08.2021.
//
#include <cstdint>
#include "iostream"
#include "server_packet.h"
#include "../Slave.h"

packet* getPacket(aocMessage *msg, const int slave_id) {
    auto* result = new packet;
    result->type = msg->type;
    result->owner = slave_id;
    switch(msg->type){
        case ServerPacket::LOGIN_SEED: {
            auto* packet = new LoginSeed;
            packet->key = AOC_STR(msg->argv[0]);
            result->data = packet;
            break;
        }
        case ServerPacket::LOGIN_OK: {
            // This Packet is Empty
            break;
        }
        case ServerPacket::LOGIN_ERROR: {
            auto* packet = new LoginError;
            packet->message = AOC_STR(msg->argv[0]);
            result->data = packet;
            break;
        }
        case ServerPacket::LOGIN_CHARLIST: {
            auto* packet = new LoginCharacterList;
            int nchars = aocMsgArraySize(msg, 0), i;
            packet->characters.resize(nchars);
            for (i = 0; i < nchars; i++) {
                int user_id = AOC_INT(aocMsgArrayValue(msg, 0, i, nullptr, nullptr));
                char* charname = AOC_STR(aocMsgArrayValue(msg, 1, i, nullptr, nullptr));
                int level = AOC_INT(aocMsgArrayValue(msg, 2, i, nullptr, nullptr));
                bool status = *(bool*)aocMsgArrayValue(msg, 3, i, nullptr, nullptr);
                character user{user_id, charname, level, status};
                packet->characters[i] = user;
            }
            packet->existing = nchars;
            result->data = packet;
            break;

        }
        case ServerPacket::CLIENT_UNKNOWN: {
            auto *packet = new CharacterUnknown;
            packet->char_id = AOC_INT(msg->argv[0]);
            result->data = packet;
            break;
        }
        case ServerPacket::CLIENT_NAME: {
            auto* packet = new CharacterName;
            packet->char_id = AOC_INT(msg->argv[0]);
            packet->name = AOC_STR(msg->argv[1]);
            result->data = packet;
            break;

        }
        case ServerPacket::LOOKUP_RESULT: {
            auto* packet = new CharacterLookup;
            packet->char_id = AOC_INT(msg->argv[0]);
            packet->name = AOC_STR(msg->argv[1]);
            result->data = packet;
            break;
        }
        case ServerPacket::PRIVATE_MSG: {
            auto* packet = new PrivateMessage;
            packet->char_id = AOC_INT(msg->argv[0]);
            packet->message = (unsigned char*) AOC_STR(msg->argv[1]);
            packet->message_len = msg->argl[1];
            packet->blob = (unsigned char*) AOC_STR(msg->argv[2]);
            packet->message_len = msg->argl[2];
            result->data = packet;
            break;
        }
        case ServerPacket::VICINITY_MSG: {
            auto* packet = new VicinityMessage;
            packet->char_id = AOC_INT(msg->argv[0]);
            packet->message = (unsigned char*) msg->argv[1];
            packet->message_len = msg->argl[1];
            packet->blob = (unsigned char*) msg->argv[2];
            packet->blob_len = msg->argl[2];
            result->data = packet;
            break;
        }
        case ServerPacket::BROADCAST_MSG: {
            auto* packet = new BroadcastMessage;
            packet->sender = AOC_STR(msg->argv[0]);
            packet->message = AOC_STR(msg->argv[1]);
            packet->blob = (unsigned char*) msg->argv[2];
            result->data = packet;
            break;
        }
        case ServerPacket::SIMPLE_SYSTEM_MSG: {
            auto* packet = new SimpleSystemMessage;
            packet->message = AOC_STR(msg->argv[0]);
            result->data = packet;
            break;
        }
        case ServerPacket::SYSTEM_MESSAGE: {
            auto* packet = new SystemMessage;
            packet->client_id = AOC_INT(msg->argv[0]);
            packet->window_id = AOC_INT(msg->argv[1]);
            packet->message_id = AOC_INT(msg->argv[2]);
            packet->message_args = AOC_STR(msg->argv[3]);
            result->data = packet;
            break;
        }
        case ServerPacket::BUDDY_STATUS: {
            auto* packet = new BuddyStatus;
            packet->char_id = AOC_INT(msg->argv[0]);
            packet->online = AOC_INT(msg->argv[1]);
            packet->status = AOC_INT(msg->argv[2]);
            result->data = packet;
            break;
        }
        case ServerPacket::BUDDY_REMOVED: {
            auto* packet = new BuddyRemoved;
            packet->char_id = AOC_INT(msg->argv[0]);
            result->data = packet;
            break;
        }
        case ServerPacket::PRIVGRP_INVITE: {
            auto* packet = new PrivateChannelInvited;
            packet->private_channel_id = AOC_INT(msg->argv[0]);
            result->data = packet;
            break;
        }
        case ServerPacket::PRIVGRP_KICK: {
            auto* packet = new PrivateChannelKicked;
            packet->private_channel_id = AOC_INT(msg->argv[0]);
            result->data = packet;
            break;
        }
        case ServerPacket::PRIVGRP_PART: {
            auto* packet = new PrivateChannelLeft;
            packet->private_channel_id = AOC_INT(msg->argv[0]);
            result->data = packet;
            break;
        }
        case ServerPacket::PRIVGRP_CLIJOIN: {
            auto* packet = new PrivateChannelClientJoined;
            packet->private_channel_id = AOC_INT(msg->argv[0]);
            packet->char_id = AOC_INT(msg->argv[1]);
            result->data = packet;
            break;
        }
        case ServerPacket::PRIVGRP_CLIPART: {
            auto* packet = new PrivateChannelClientLeft;
            packet->private_channel_id = AOC_INT(msg->argv[0]);
            packet->char_id = AOC_INT(msg->argv[1]);
            result->data = packet;
            break;
        }
        case ServerPacket::PRIVGRP_MSG: {
            auto* packet = new PrivateChannelMessage;
            packet->private_channel_id = AOC_INT(msg->argv[0]);
            packet->char_id = AOC_INT(msg->argv[1]);
            packet->message = AOC_STR(msg->argv[2]);
            packet->blob = (unsigned char*) msg->argv[3];
            result->data = packet;
            break;
        }
//         Does this one exist?
        case ServerPacket::PRIVGRP_INV_REF: {
            printf("ID %d: [%d] -> %d | %s | %s",
                   ServerPacket::PRIVGRP_INV_REF,
                   AOC_INT(msg->argv[0]),
                   AOC_INT(msg->argv[1]),
                   AOC_STR(msg->argv[2]),
                   AOC_STR(msg->argv[3])
                   );
//            auto* packet = new PrivateChannelInviteRefused;
//            packet->private_channel_id = AOC_INT(msg->argv[0]);
//            packet->char_id = AOC_INT(msg->argv[1]);
//            result->data = packet;
//            break;
        }
        case ServerPacket::GROUP_INFO: {
            auto* packet = new PublicChannelJoined;
            packet->channel_id = (unsigned char*)msg->argv[0];
            packet->name = AOC_STR(msg->argv[1]);
            packet->unknown = AOC_INT(msg->argv[2]);
            packet->flags = AOC_STR(msg->argv[3]);
            result->data = packet;
            break;
        }
        case ServerPacket::GROUP_PART: {
            auto* packet = new PublicChannelLeft;
            packet->channel_id = (unsigned char*)msg->argv[0];
            result->data = packet;
            break;
        }
        case ServerPacket::GROUP_MSG: {
            auto* packet = new PublicChannelMessage;
            packet->channel_id = (unsigned char*)msg->argv[0];
            packet->char_id = AOC_INT(msg->argv[1]);
            packet->message = AOC_STR(msg->argv[2]);
            packet->blob = AOC_STR(msg->argv[3]);
            result->data = packet;
            break;
        }
        case ServerPacket::PONG: {
            auto* packet = new Pong;
            packet->blob = AOC_STR(msg->argv[0]);
            result->data = packet;
            break;
        }
        default:
            std::cout << msg->type << std::endl;
    }
    return result;
}
void delPacket(packet *p){
    switch (p->type) {
        case ServerPacket::LOGIN_SEED: {
            delete (LoginSeed*) p->data;
            break;
        }
        case ServerPacket::LOGIN_OK: {
            // Packet is empty
            break;
        }
        case ServerPacket::LOGIN_ERROR: {
            delete (LoginError *) p->data;
            break;
        }
        case ServerPacket::LOGIN_CHARLIST: {
            delete (LoginCharacterList *) p->data;
            break;
        }
        case ServerPacket::CLIENT_UNKNOWN: {
            delete (CharacterUnknown*) p->data;
            break;
        }
        case ServerPacket::CLIENT_NAME: {
            delete (CharacterName *) p->data;
            break;
        }
        case ServerPacket::LOOKUP_RESULT: {
            delete (CharacterLookup*) p->data;
            break;
        }
        case ServerPacket::PRIVATE_MSG: {
            delete (PrivateMessage*) p->data;
            break;
        }
        case ServerPacket::VICINITY_MSG: {
            delete (VicinityMessage*) p->data;
            break;
        }
        case ServerPacket::BROADCAST_MSG: {
            delete (BroadcastMessage*) p->data;
            break;
        }
        case ServerPacket::SIMPLE_SYSTEM_MSG: {
            delete (SimpleSystemMessage*) p->data;
            break;
        }
        case ServerPacket::SYSTEM_MESSAGE: {
            delete (SystemMessage*) p->data;
            break;
        }
        case ServerPacket::BUDDY_STATUS: {
            delete (BuddyStatus*) p->data;
            break;
        }
        case ServerPacket::BUDDY_REMOVED: {
            delete (BuddyRemoved*) p->data;
            break;
        }
        case ServerPacket::PRIVGRP_INVITE: {
            delete (PrivateChannelInvited*) p->data;
            break;
        }
        case ServerPacket::PRIVGRP_KICK: {
            delete (PrivateChannelKicked*) p->data;
            break;
        }
        case ServerPacket::PRIVGRP_PART: {
            delete (PrivateChannelLeft*) p->data;
            break;
        }
        case ServerPacket::PRIVGRP_CLIJOIN: {
            delete (PrivateChannelInvited*) p->data;
            break;
        }
        case ServerPacket::PRIVGRP_CLIPART: {
            delete (PrivateChannelClientLeft*) p->data;
            break;
        }
        case ServerPacket::PRIVGRP_MSG: {
            delete (PrivateChannelMessage*) p->data;
            break;
        }
        case ServerPacket::GROUP_INFO: {
            delete (PublicChannelJoined*) p->data;
            break;
        }
        case ServerPacket::GROUP_PART: {
            delete (PublicChannelLeft*) p->data;
            break;
        }
        case ServerPacket::GROUP_MSG: {
            delete (PublicChannelMessage*) p->data;
            break;
        }
        case ServerPacket::PONG: {
            delete (Pong*) p->data;
            break;
        }
    }
    delete p;
}
