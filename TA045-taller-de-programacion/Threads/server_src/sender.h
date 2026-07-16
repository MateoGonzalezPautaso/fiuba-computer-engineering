#ifndef SENDER_H
#define SENDER_H

#include <atomic>

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "server_protocol.h"

class Sender: public Thread {
public:
    Sender(ServerProtocol& srv_prot, Queue<GameEvent>& queue);

    virtual void run() override;
    virtual void stop() override;

    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

private:
    ServerProtocol& srv_prot;
    Queue<GameEvent>& queue;  // send to Client

    std::atomic<bool> _already_stopped{false};
};

#endif
