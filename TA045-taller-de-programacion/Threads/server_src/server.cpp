#include "server.h"

#include <iostream>


Server::Server(const std::string& servname):
        npc_config(),
        input_queue(),
        monitor(),
        acceptor(servname, monitor, input_queue, npc_config),
        game_loop(input_queue, monitor, npc_config) {}

void Server::run() {
    acceptor.start();
    game_loop.start();

    char c = 0;
    while (c != 'q') {
        if (!(std::cin >> c))
            break;
    }

    acceptor.stop();
    game_loop.stop();

    acceptor.join();
    game_loop.join();
}
