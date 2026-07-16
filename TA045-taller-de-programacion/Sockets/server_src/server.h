#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "game.h"
#include "server_protocol.h"
#include "server_view.h"

class Server {
private:
    std::string servname;
    std::string file_path;
    bool is_binary;

    ServerView view;

    void handle_session(ServerProtocol& srv_prot, const std::string& username);

    void handle_buy(const std::string& username, const CommandInfo& cmd_info, Game& game);
    void handle_sell(const std::string& username, const CommandInfo& cmd_info, Game& game);

public:
    Server(const std::string& servname, const std::string& file_path, bool is_binary);

    void run();
};

#endif
