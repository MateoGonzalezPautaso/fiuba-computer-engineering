#include "client_parser.h"

CommandInfo Parser::parse_input(const std::string& line) const {
    CommandInfo cmd_info;

    if (line == "tienda") {
        cmd_info.type = Command::STORE;
    } else if (line == "inventario") {
        cmd_info.type = Command::INVENTORY;
    } else if (line == "salir") {
        cmd_info.type = Command::QUIT;
        // cppcheck-suppress stlIfStrFind
    } else if (line.find("comprar ") == 0) {
        cmd_info.object_name = line.substr(8);
        cmd_info.type = Command::BUY;
        // cppcheck-suppress stlIfStrFind
    } else if (line.find("vender ") == 0) {
        cmd_info.object_name = line.substr(7);
        cmd_info.type = Command::SELL;
    } else {
        cmd_info.type = Command::INVALID;
    }

    // .find() is C++17 and .starts_with() is C++20

    return cmd_info;
}
