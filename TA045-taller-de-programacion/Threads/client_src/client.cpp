#include "client.h"

#include <iostream>
#include <string>

#include "../common_src/socket.h"

#include "client_parser.h"

Client::Client(const std::string& hostname, const std::string& servname):
        hostname(hostname), servname(servname) {}


void Client::run() {
    Socket skt(hostname.c_str(), servname.c_str());
    ClientProtocol clt_prot(skt, npc_config);

    std::string username = get_username();
    clt_prot.send_username(username);

    handle_session(clt_prot);
}

std::string Client::get_username() const {
    std::string username;

    while (username.empty()) {
        view.show_ask_name();

        if (!std::getline(std::cin, username)) {
            if (std::cin.eof())
                throw std::runtime_error("EOF while asking for name");

            std::cin.clear();  // clean just in case of weird failure
            view.show_invalid_username_error();
            continue;
        }

        if (username.empty())
            view.show_invalid_username_error();
    }

    return username;
}


void Client::handle_session(ClientProtocol& clt_prot) {
    Parser parser;
    std::string line;

    while (std::getline(std::cin, line)) {
        CommandInfo cmd_info = parser.parse_input(line, npc_config);

        if (cmd_info.type == Command::EXIT)
            break;

        if (cmd_info.type == Command::INVALID) {
            view.show_invalid_operation_error();
            continue;
        }

        switch (cmd_info.type) {
            case Command::READ:
                handle_read(clt_prot, cmd_info);
                break;

            case Command::DEFEAT:
                clt_prot.send_defeat(cmd_info.npc_code.value());
                break;

            default:
                break;
        }
    }
}

void Client::handle_read(ClientProtocol& clt_prot, const CommandInfo& cmd_info) {
    uint16_t n = cmd_info.n_msg.value();

    for (uint16_t i = 0; i < n; ++i) {
        GameEvent event = clt_prot.recv_event();
        view.show_event(event, npc_config);
    }
}
