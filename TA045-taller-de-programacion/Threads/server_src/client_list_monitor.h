#ifndef CLIENT_LIST_MONITOR_H
#define CLIENT_LIST_MONITOR_H

#include <cstdint>
#include <map>
#include <mutex>

#include "client_handler.h"

class ClientListMonitor {
public:
    ClientListMonitor();

    void add(uint32_t id, Socket skt, Queue<PlayerCommand>& input_queue,
             const NPCConfig& npc_config);

    void broadcast(const GameEvent& event);

    void clean_dead();  // delete dead clients

    ~ClientListMonitor();

    ClientListMonitor(const ClientListMonitor&) = delete;
    ClientListMonitor& operator=(const ClientListMonitor&) = delete;

private:
    std::mutex mtx;
    std::map<uint32_t, ClientHandler*> clients;  // id -> ClientHandler

    void stop_all();  // used by destructor when server closes
};

#endif
