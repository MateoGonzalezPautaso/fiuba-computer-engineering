#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "../common_src/queue.h"

#include "acceptor.h"
#include "client_list_monitor.h"
#include "game_loop.h"


class Server {
public:
    explicit Server(const std::string& servname);

    void run();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

private:
    NPCConfig npc_config;

    Queue<PlayerCommand> input_queue;
    ClientListMonitor monitor;

    Acceptor acceptor;
    GameLoop game_loop;
};

#endif
