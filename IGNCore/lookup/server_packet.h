//
// Created by Cedric on 31.08.2021.
//

#ifndef PACKETLINK_SERVER_PACKET_H
#define PACKETLINK_SERVER_PACKET_H

#include "../packet.h"
#include "aochat.h"
template<class T> class Pointer{
    T* m_ptr;
public:
    Pointer(T* ptr= nullptr): m_ptr(ptr){}
    ~Pointer(){ delete m_ptr;}
    T& operator*() const{return *m_ptr;}
    T* operator->() const{return m_ptr;}
};
namespace ServerPacket{
    const int LOGIN_SEED        = 0;        /* [string Seed] */
    const int LOGIN_OK          = 5;        /* - */
    const int LOGIN_ERROR       = 6;        /* [string Message] */
    const int LOGIN_CHARLIST    = 7;        /* {[int UserID]} {[string Name]} {[int Level]} {[int Online]} */
    const int CLIENT_UNKNOWN    = 10;        /* [int UserID] */
    const int CLIENT_NAME       = 20;        /* [int UserID] [string Name] */
    const int LOOKUP_RESULT     = 21;        /* [int UserID] [string Name] */
    const int PRIVATE_MSG       = 30;        /* [int UserID] [string Text] [string Blob] */
    const int VICINITY_MSG      = 34;        /* [int UserID] [string Text] [string Blob] */
    const int BROADCAST_MSG  = 35;        /* [string] [string Text] [string Blob] */
    const int SIMPLE_SYSTEM_MSG        = 36;        /* [string Text] */
    const int SYSTEM_MESSAGE       = 37;        /* [int] [int] [int] [string] */
    const int BUDDY_STATUS      = 40;        /* [int UserID] [int Online] [string Status] */
    const int BUDDY_REMOVED     = 41;        /* [int UserID] */
    const int PRIVGRP_INVITE    = 50;        /* [int UserID] */
    const int PRIVGRP_KICK      = 51;        /* [int UserID] */
    const int PRIVGRP_PART      = 53;        /* [int UserID] */
    const int PRIVGRP_CLIJOIN   = 55;        /* [int UserID] [int UserID] */
    const int PRIVGRP_CLIPART   = 56;        /* [int UserID] [int UserID] */
    const int PRIVGRP_MSG       = 57;        /* [int UserID] [int UserID] [string Text] [string Blob] */
    const int PRIVGRP_INV_REF       = 58;        /* [int UserID] [int UserID] [string Text] [string Blob] */
    const int GROUP_INFO        = 60;        /* [grp GroupID] [string GroupName] [word Mute] [word ?] [string ?] */
    const int GROUP_PART        = 61;        /* [grp GroupID] */
    const int GROUP_MSG         = 65;        /* [grp GroupID] [int UserID] [string Text] [string Blob] */
    const int PONG              = 100;        /* [string Whatever] */
    const int FORWARD           = 110;        /* [int ?] [raw Data] */
    const int AMD_MUX_INFO      = 1100;    /* {[int ?]} {[int ?]} {[int ?]} */
}

const int LOGIN_RESPONSE        = 2;        /* [int ?] [string Username] [string Key] */
const int LOGIN_SELCHAR         = 3;        /* [int UserID] */
const int NAME_LOOKUP           = 21;        /* [string Name] */
const int PRIVATE_MSG           = 30;        /* [int UserID] [string Text] [string Blob] */
const int BUDDY_ADD             = 40;        /* [int UserID] [string Status] */
const int BUDDY_REMOVE          = 41;        /* [int UserID] */
const int ONLINE_STATUS         = 42;        /* [int ?] */
const int PRIVGRP_INVITE        = 50;        /* [int UserID] */
const int PRIVGRP_KICK          = 51;        /* [int UserID] */
const int PRIVGRP_JOIN          = 52;        /* [int UserID] */
const int PRIVGRP_KICKALL       = 54;        /* - */
const int PRIVGRP_MSG           = 57;        /* [int UserID] [string Text] [string Blob] */
const int GROUP_DATASET         = 64;        /* [grp GroupID] [word Mute] [int ?] */
const int GROUP_MESSAGE         = 65;        /* [grp GroupID] [string text] [string Blob] */
const int GROUP_CLIMODE         = 66;        /* [grp GroupID] [int ?] [int ?] [int ?] [int ?] sent when zoning in game? */
const int CLIMODE_GET           = 70;        /* [int ?] [grp GroupID] */
const int CLIMODE_SET           = 71;        /* [int ?] [int ?] [int ?] [int ?] */
const int PING                  = 100;        /* [string Whatever] */
const int CHAT_COMMAND          = 120;        /* {[string Command] [string Value]...} */
packet *getPacket(aocMessage *, int slave_id);

void delPacket(packet *);

#endif //PACKETLINK_SERVER_PACKET_H
