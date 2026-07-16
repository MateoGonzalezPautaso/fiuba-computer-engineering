#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <string>

#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "client_list_monitor.h"

class Acceptor: public Thread {
public:
    Acceptor(const std::string& servname, ClientListMonitor& monitor,
             Queue<PlayerCommand>& input_queue, const NPCConfig& npc_config);

    virtual void run() override;
    virtual void stop() override;

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

private:
    Socket listener;
    ClientListMonitor& monitor;
    Queue<PlayerCommand>& input_queue;
    uint32_t next_player_id;
    const NPCConfig& npc_config;
};


#endif
