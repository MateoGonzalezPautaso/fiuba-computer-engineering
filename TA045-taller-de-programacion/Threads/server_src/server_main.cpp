#include <exception>
#include <iostream>

#include "server.h"

//#include "server_single_test.cpp" // ONLY TESTING SINGLE THREAD

int main(int argc, const char* const argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servicename or port>\n";
            return 1;
        }

        std::string servname = argv[1];

        // ONLY TESTING SINGLE THREAD
        // Server_SS_Test server(servname);
        // server.run();

        Server server(servname);
        server.run();

        return 0;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return 1;
    }
}
