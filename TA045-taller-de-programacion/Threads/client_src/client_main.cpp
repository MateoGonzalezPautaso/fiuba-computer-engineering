#include <exception>
#include <iostream>

#include "client.h"

int main(int argc, const char* const argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Bad program call. Expected " << argv[0]
                      << " <hostname or IP> <servicename or port>\n";
            return 1;
        }

        std::string hostname = argv[1];
        std::string servname = argv[2];

        Client client(hostname, servname);
        client.run();

        return 0;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return 1;
    }
}
