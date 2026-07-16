
#include "server.h"

#include <stdexcept>

void Server::handle_buy(const std::string& username, const CommandInfo& cmd_info, Game& game) {
    std::string object_name = cmd_info.object_name.value();
    if (!object_name.empty()) {
        object_name[0] = std::toupper(object_name[0]);
    }

    BuyResult result = game.process_buy(static_cast<ItemCode>(cmd_info.item_code.value()));

    view.show_buy_result(username, object_name, result);
}

void Server::handle_sell(const std::string& username, const CommandInfo& cmd_info, Game& game) {
    std::string object_name = cmd_info.object_name.value();
    if (!object_name.empty()) {
        object_name[0] = std::toupper(object_name[0]);
    }

    SellResult result = game.process_sell(static_cast<ItemCode>(cmd_info.item_code.value()));

    view.show_sell_result(username, object_name, result);
}

Server::Server(const std::string& servname, const std::string& file_path, bool is_binary):
        servname(servname), file_path(file_path), is_binary(is_binary) {}

void Server::run() {
    // the socket needs const char* so we use .c_str()
    Socket srv(servname.c_str());
    Socket peer = srv.accept();

    ServerProtocol srv_prot(peer, is_binary);

    std::string username = srv_prot.recv_username();

    view.show_connection(username);

    srv_prot.send_protocol_type();

    handle_session(srv_prot, username);
}

void Server::handle_session(ServerProtocol& srv_prot, const std::string& username) {
    Game game(file_path);

    CommandInfo cmd_info;

    while (true) {

        try {
            // if object_name is invalid, throw an exception
            cmd_info = srv_prot.recv_command();
        } catch (const std::invalid_argument& e) {
            view.show_invalid_item_error(username);
            continue;
        }

        switch (cmd_info.type) {
            case Command::STORE:
                srv_prot.send_store(game.get_store_items());
                break;

            case Command::INVENTORY:
                srv_prot.send_inventory(game.get_gold(), game.get_inventory());
                break;

            case Command::BUY:
                handle_buy(username, cmd_info, game);
                break;

            case Command::SELL:
                handle_sell(username, cmd_info, game);
                break;

            case Command::QUIT: {
                view.show_disconnection(username);
                return;
            }

            default:
                view.show_invalid_item_error(username);
                break;
        }
    }
}
