#include "client_view.h"

#include <iostream>

// client is single thread so std::cout can be
// used and is more efficient than std::ostringstream

void ClientView::show_ask_name() const { std::cout << "What is your name?\n"; }

void ClientView::show_event(const GameEvent& event, const NPCConfig& npc_config) const {
    common_view.show_event(event, npc_config);
}

void ClientView::show_invalid_username_error() const {
    std::cout << "Invalid username, try again\n";
}

void ClientView::show_invalid_operation_error() const { std::cout << "Invalid operation\n"; }
