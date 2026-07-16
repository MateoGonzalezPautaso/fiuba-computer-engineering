#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>

#include "../common_src/queue.h"
#include "../common_src/socket.h"

#include "receiver.h"
#include "sender.h"
#include "server_protocol.h"

class ClientHandler {
public:
    ClientHandler(Socket skt_acceptor, Queue<PlayerCommand>& input_queue,
                  const NPCConfig& npc_config);

    void start();
    void stop();
    void join();

    bool is_alive() const;

    void push_event(const GameEvent& event);

    ~ClientHandler();

    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;

private:
    Socket skt;  // moved from Acceptor
    ServerProtocol srv_prot;
    Queue<GameEvent> queue;  // output_queue from Sender

    std::atomic<bool> _already_stopped{false};

    Sender sender;
    Receiver receiver;
};

#endif
