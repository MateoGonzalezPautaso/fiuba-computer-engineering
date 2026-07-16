#include "client_list_monitor.h"

#include <utility>


ClientListMonitor::ClientListMonitor() {}

void ClientListMonitor::add(uint32_t id, Socket skt, Queue<PlayerCommand>& input_queue,
                            const NPCConfig& npc_config) {
    std::lock_guard<std::mutex> lock(mtx);

    clients[id] = new ClientHandler(std::move(skt), input_queue,
                                    npc_config);  // not thread-safe, so lock the mutex
    clients[id]->start();
}

void ClientListMonitor::broadcast(const GameEvent& event) {
    std::lock_guard<std::mutex> lock(mtx);

    for (auto& pair: clients) {
        ClientHandler* client = pair.second;
        try {
            client->push_event(event);
        } catch (const ClosedQueue&) {
            // avoid closing connection for everyone
        }
    }
}

void ClientListMonitor::clean_dead() {
    // use when ClientHandler is dead
    std::lock_guard<std::mutex> lock(mtx);

    auto it = clients.begin();

    while (it != clients.end()) {
        ClientHandler* client = it->second;

        // if client is dead, free memory
        if (!client->is_alive()) {
            delete client;           // free memory
            it = clients.erase(it);  // delete key from map
        } else {
            it++;  // if alive, iterate to next Clienthandler
        }
    }
}

void ClientListMonitor::stop_all() {
    // use when server closes
    std::lock_guard<std::mutex> lock(mtx);

    for (const auto& pair: clients) {
        ClientHandler* client = pair.second;
        delete client;
    }

    clients.clear();
}

ClientListMonitor::~ClientListMonitor() { stop_all(); }
