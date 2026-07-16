#ifndef SERVER_VIEW_H
#define SERVER_VIEW_H

#include <string>

#include "game_results.h"

class ServerView {
public:
    void show_connection(const std::string& username) const;
    void show_disconnection(const std::string& username) const;
    void show_buy_result(const std::string& username, const std::string& item_name,
                         BuyResult result) const;
    void show_sell_result(const std::string& username, const std::string& item_name,
                          SellResult result) const;
    void show_invalid_item_error(const std::string& username) const;
};

#endif
