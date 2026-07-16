#include "client_handler.h"

#include <utility>

ClientHandler::ClientHandler(Socket skt_acceptor, Queue<PlayerCommand>& input_queue,
                             const NPCConfig& npc_config):
        skt(std::move(skt_acceptor)),
        srv_prot(skt, npc_config),
        queue(),
        sender(srv_prot, queue),
        receiver(srv_prot, input_queue, sender) {}

void ClientHandler::start() {
    sender.start();
    receiver.start();
}

void ClientHandler::stop() {
    if (_already_stopped)
        return;

    _already_stopped = true;
    receiver.stop();  // closes socket and wakes up Receiver
    sender.stop();    // closes output_queue and wakes up Sender
}

void ClientHandler::join() {
    sender.join();
    receiver.join();
}

bool ClientHandler::is_alive() const {
    bool alive = (receiver.is_alive() && sender.is_alive());
    return alive;
}

void ClientHandler::push_event(const GameEvent& event) { queue.try_push(event); }

ClientHandler::~ClientHandler() {
    stop();
    join();
}
