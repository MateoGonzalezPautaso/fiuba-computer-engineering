#include "client_view.h"

#include <iostream>

void ClientView::show_store(const std::vector<Item>& items) const {
    std::cout << "Tienda:\n";

    // print if stock = 0
    for (const Item& item: items) {
        std::cout << "    - " << item.name << " (" << item.stock << ") - Compra: " << item.buy_price
                  << " - Venta: " << item.sell_price << "\n";
    }
}

void ClientView::show_inventory(uint16_t gold, const std::vector<Item>& items) const {
    std::cout << "Inventario:\n";
    std::cout << "    - Oro: " << gold << "\n";

    for (const Item& item: items) {
        std::cout << "    - " << item.name << " (" << item.stock << ")\n";
    }
}

void ClientView::show_invalid_operation() const {
    std::cout << "Operacion invalida"
              << "\n";
}

void ClientView::show_invalid_object_error() const {
    std::cout << "Objeto invalido, intenta nuevamente.\n";
}
