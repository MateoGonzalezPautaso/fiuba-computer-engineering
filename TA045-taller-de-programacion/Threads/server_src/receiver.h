#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>

#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "player_command.h"
#include "sender.h"
#include "server_protocol.h"


class Receiver: public Thread {
public:
    Receiver(ServerProtocol& srv_prot, Queue<PlayerCommand>& queue, Sender& sender);

    virtual void run() override;
    virtual void stop() override;

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

private:
    std::string username;

    ServerProtocol& srv_prot;
    Queue<PlayerCommand>& queue;
    Sender& sender;
};


#endif
