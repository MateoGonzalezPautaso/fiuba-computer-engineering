#include "sender.h"

Sender::Sender(ServerProtocol& srv_prot, Queue<GameEvent>& queue):
        srv_prot(srv_prot), queue(queue) {}

void Sender::run() {
    try {
        while (true) {
            GameEvent event = queue.pop();  // sleeps while queue is empty
            srv_prot.send_event(event);
        }
    } catch (const ClosedQueue&) {
        // someone called stop()
        // ClosedQueue has an exception message
    }
}

void Sender::stop() {
    if (_already_stopped)
        return;

    _already_stopped = true;
    queue.close();  // wakes up pop()
}
