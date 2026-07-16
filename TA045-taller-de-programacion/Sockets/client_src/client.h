#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "client_protocol.h"
#include "client_view.h"

class Client {
private:
    std::string hostname;
    std::string servname;
    std::string username;

    ClientView view;

    void handle_session(ClientProtocol& clt_prot);

    void handle_store(ClientProtocol& clt_prot);
    void handle_inventory(ClientProtocol& clt_prot);

public:
    Client(const std::string& hostname, const std::string& servname, const std::string& username);

    void run();
};

#endif
