#ifndef CLIENT_VIEW_H
#define CLIENT_VIEW_H

#include "../common_src/common_view.h"
#include "../common_src/game_event.h"

class ClientView {
public:
    void show_ask_name() const;
    void show_invalid_username_error() const;
    void show_invalid_operation_error() const;

    void show_event(const GameEvent& event, const NPCConfig& npc_config) const;

private:
    CommonView common_view;
};

#endif
