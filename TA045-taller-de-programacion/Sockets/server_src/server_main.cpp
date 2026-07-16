#include <exception>
#include <iostream>

#include "server.h"

int main(int argc, const char* const argv[]) {
    try {
        int ret = -1;

        if (argc != 4) {
            std::cerr << "Bad program call. Expected " << argv[0]
                      << " <servname> <file_path> <binary|text>\n";
            return ret;
        }

        std::string servname = argv[1];
        std::string file_path = argv[2];
        std::string prot_type = argv[3];

        if (prot_type != "binario" && prot_type != "texto") {
            throw std::runtime_error("The protocol must be 'binario' or 'texto'");
        }

        bool is_binary = (prot_type == "binario");

        Server server(servname, file_path, is_binary);
        server.run();

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
