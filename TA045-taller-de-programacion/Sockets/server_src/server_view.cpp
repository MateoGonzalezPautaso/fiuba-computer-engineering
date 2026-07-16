#include "server_view.h"

#include <iostream>

void ServerView::show_connection(const std::string& username) const {
    std::cout << "Jugador conectado: " << username << '\n';
}

void ServerView::show_disconnection(const std::string& username) const {
    std::cout << "Jugador desconectado: " << username << "\n";
}

void ServerView::show_invalid_item_error(const std::string& username) const {
    std::cout << "Invalid operation"
              << "\n";
}


void ServerView::show_buy_result(const std::string& username, const std::string& item_name,
                                 BuyResult result) const {
    switch (result) {
        case BuyResult::SUCCESS:
            std::cout << "El jugador " << username << " compro " << item_name << "\n";
            break;

        case BuyResult::NO_STOCK:
            std::cout << "El jugador " << username << " intento comprar " << item_name
                      << " pero no habia stock disponible\n";
            break;

        case BuyResult::NOT_ENOUGH_GOLD:
            std::cout << "El jugador " << username << " no tiene suficiente oro para comprar "
                      << item_name << "\n";
            break;

        default:
            break;
    }
}

void ServerView::show_sell_result(const std::string& username, const std::string& item_name,
                                  SellResult result) const {
    switch (result) {
        case SellResult::SUCCESS:
            std::cout << "El jugador " << username << " vendio " << item_name << "\n";
            break;

        case SellResult::ITEM_NOT_IN_INVENTORY:
            std::cout << "El jugador " << username << " no tiene stock de " << item_name
                      << " para vender\n";
            break;

        default:
            break;
    }
}
