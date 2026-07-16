#include <exception>
#include <iostream>

#include "client.h"
#include "client_parser.h"
#include "client_protocol.h"

int main(int argc, const char* const argv[]) {
    try {
        int ret = -1;

        if (argc != 4) {
            std::cerr << "Bad program call. Expected " << argv[0]
                      << " <hostname> <servname> <username>\n";
            return ret;
        }

        std::string hostname = argv[1];
        std::string servname = argv[2];
        std::string username = argv[3];

        Client client(hostname, servname, username);
        client.run();

        ret = 0;
        return ret;

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
