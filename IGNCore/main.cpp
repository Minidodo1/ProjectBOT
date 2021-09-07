#include <iostream>
#include "Slave.h"
#include <thread>

BuddyListService* bsl = nullptr;
bool running = true;
Registry* r;

struct bot {
    std::thread process;
    Slave *main{};
};
std::vector<bot *> threads;
int run_slave(Slave *s, log_info* logInfo) {
    return s->connect(logInfo, r);
}

/* Wrapper for aocNameListLookupByUID() */

int main() {
    r = new Registry;
#ifdef _WIN32
    struct WSAData wd;

    /* On windows we need to initialize WinSock */
    WSAStartup(0x0101, &wd);
#endif
    std::vector<log_info *> accounts{new log_info{"Account", "Password", "Character"}};

    // Technically no longer needed, but I've been too lazy to remove it.

    r->setEventService(new EventService);
    r->setLookupService(new LookupService);
    bsl = new BuddyListService(r);
    r->setBuddyList(bsl);
    for (const auto &item : accounts) {
        bot *a = new bot;
        a->main = new Slave;
        a->process = std::thread(run_slave, a->main, item);
        threads.push_back(a);
    }
    accounts.clear();

    // Only perform the "terminated yet?" check every 10 seconds
    while (running) {
        using namespace std;
        this_thread::sleep_for(10s);
        for (const auto &item : threads) {
            if (!item->main->getRunning()) {
                running = false;
                continue;
            }
        }
    }
    for (const auto &item : threads) {
        item->main->setRunning(false);
    }
    for (const auto &item : threads) {
        item->process.join();
        delete item;
    }

    return 0;
}

LookupService *Registry::getLookupService() {return this->ls;}
EventService *Registry::getEventService()  {return this->es;}
BuddyListService *Registry::getBuddyListService() {return this->bls;}
CommandService *Registry::getCommandService() {return this->cs;}

void Registry::setBuddyList(BuddyListService *param) {this->bls = param;}

void Registry::setEventService(EventService *param) {this->es = param;}

void Registry::setCommandService(CommandService *param) {this->cs = param;}

void Registry::setLookupService(LookupService *param) {this->ls = param;}
