//
// Created by Cedric on 31.08.2021.
//

#ifndef AOBOT_PACKET_H
#define AOBOT_PACKET_H
#include <vector>
#include <pthread.h>

struct character{
    int user_id;
    char* char_name;
    int level;
    bool status;
};

struct packet {
    int type = -1;
    int owner;
    void* data = nullptr;
};
struct LoginSeed{
    char* key;
};
// Packet 6
struct LoginError{
    char* message = nullptr;
};
// Packet 7
struct LoginCharacterList{
    int existing = 0;
    std::vector<character> characters;
    character chars[20000];
};
// Packet 10
struct CharacterUnknown{
    int char_id = -1;
};
// Packet 20
struct CharacterName{
    int char_id = -1;
    char* name = nullptr;
};
// Packet 21
struct CharacterLookup{
    int char_id = -1;
    char* name = nullptr;
};

// Packet 30
struct PrivateMessage{
    int char_id;
    unsigned char* message;
    int message_len, blob_len;
    unsigned char* blob;
};
// Packet 34
struct VicinityMessage{
    int char_id;
    unsigned char* message;
    int message_len, blob_len;
    unsigned char* blob;
};
// Packet 35
struct BroadcastMessage{
    char* sender;
    char* message;
    unsigned char* blob;
};
// Packet 36
struct SimpleSystemMessage{
    char* message;
};
// Packet 37
struct SystemMessage{
    int client_id, window_id, message_id;
    char* message_args;

};

// Packet 40
struct BuddyStatus{
    int char_id;
    bool online;
    bool status;
};
// Packet 41
struct BuddyRemoved{
    int char_id;
};
// Packet 50
struct PrivateChannelInvited{
    int private_channel_id;
};

// Packet 51
struct PrivateChannelKicked{
    int private_channel_id;
};
// Packet 53
struct PrivateChannelLeft{
    int private_channel_id;
};
// Packet 55
struct PrivateChannelClientJoined{
    int private_channel_id, char_id;
};
// Packet 56
struct PrivateChannelClientLeft{
    int private_channel_id, char_id;
};
// Packet 57
struct PrivateChannelMessage{
    int private_channel_id, char_id;
    const char *message;
    unsigned char* blob;
};
// Packet 58
struct PrivateChannelInviteRefused{
    int private_channel_id, char_id;
};
// Packet 60
struct PublicChannelJoined{
    unsigned char* channel_id;
    int unknown;
    char *name, *flags;
};
// Packet 61
struct PublicChannelLeft{
    unsigned char* channel_id;
};
// Packet 65
struct PublicChannelMessage{
    unsigned char* channel_id;
    int char_id;
    char *message, *blob;

};
// Packet 100
struct Pong{
    char *blob;

};

#endif //AOBOT_PACKET_H
