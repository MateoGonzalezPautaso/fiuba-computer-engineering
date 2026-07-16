#include "acceptor.h"

#include <utility>

#include <sys/socket.h>

Acceptor::Acceptor(const std::string& servname, ClientListMonitor& monitor,
                   Queue<PlayerCommand>& input_queue, const NPCConfig& npc_config):
        listener(servname.c_str()),
        monitor(monitor),
        input_queue(input_queue),
        next_player_id(1),
        npc_config(npc_config) {}

void Acceptor::run() {
    try {
        while (should_keep_running()) {
            Socket peer = listener.accept();

            uint32_t player_id = next_player_id++;

            monitor.add(player_id, std::move(peer), input_queue, npc_config);

            monitor.clean_dead();
        }
    } catch (const std::exception&) {}
}

void Acceptor::stop() {
    Thread::stop();
    listener.shutdown(SHUT_RDWR);
    listener.close();
}
