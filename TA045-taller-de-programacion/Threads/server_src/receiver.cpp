#include "receiver.h"

#include <string>

#include <sys/socket.h>

Receiver::Receiver(ServerProtocol& srv_prot, Queue<PlayerCommand>& queue, Sender& sender):
        srv_prot(srv_prot), queue(queue), sender(sender) {}

void Receiver::run() {
    try {
        username = srv_prot.recv_username();

        while (should_keep_running()) {

            CommandInfo cmd_info = srv_prot.recv_command();

            PlayerCommand player_cmd(username, cmd_info);

            queue.push(player_cmd);
        }
    } catch (const ClosedQueue&) {
        sender.stop();
    } catch (const std::exception&) {
        sender.stop();
    }
}

void Receiver::stop() {
    Thread::stop();
    srv_prot.shutdown(SHUT_RDWR);  // closes socket
}
