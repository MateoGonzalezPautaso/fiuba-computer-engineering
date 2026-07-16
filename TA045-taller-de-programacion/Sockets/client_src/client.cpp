#include "client.h"

#include <iostream>
#include <string>
#include <vector>

#include "../common_src/socket.h"

#include "client_parser.h"
#include "client_protocol.h"

Client::Client(const std::string& hostname, const std::string& servname,
               const std::string& username):
        hostname(hostname), servname(servname), username(username) {}

void Client::handle_store(ClientProtocol& clt_prot) {
    std::vector<Item> store_items = clt_prot.recv_store();

    view.show_store(store_items);
}

void Client::handle_inventory(ClientProtocol& clt_prot) {
    uint16_t gold = 0;
    std::vector<Item> inventory_items;

    clt_prot.recv_inventory(gold, inventory_items);

    view.show_inventory(gold, inventory_items);
}

void Client::run() {
    Socket skt(hostname.c_str(), servname.c_str());
    ClientProtocol clt_prot(skt);

    clt_prot.send_username(username);
    clt_prot.recv_protocol_type();

    handle_session(clt_prot);
}

void Client::handle_session(ClientProtocol& clt_prot) {
    std::string line;
    Parser parser;

    while (std::getline(std::cin, line)) {
        CommandInfo cmd_info = parser.parse_input(line);

        if (cmd_info.type == Command::QUIT)
            break;

        if (cmd_info.type == Command::INVALID) {
            view.show_invalid_operation();
            continue;
        }

        try {
            // if object_name is invalid, throw an exception
            clt_prot.send_command(cmd_info);
        } catch (const std::invalid_argument& e) {
            view.show_invalid_object_error();
            continue;
        }

        switch (cmd_info.type) {
            case Command::STORE:
                handle_store(clt_prot);
                break;

            case Command::INVENTORY:
                handle_inventory(clt_prot);
                break;

            default:
                // client does not answer to items being bought or sold
                break;
        }
    }
}
