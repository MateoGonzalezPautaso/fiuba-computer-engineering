#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "../common_src/common_view.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "client_list_monitor.h"
#include "game.h"
#include "player_command.h"

class GameLoop: public Thread {
public:
    GameLoop(Queue<PlayerCommand>& input_queue, ClientListMonitor& monitor,
             const NPCConfig& npc_config);

    virtual void run() override;
    virtual void stop() override;

    GameLoop(const GameLoop&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;

private:
    Game game;
    Queue<PlayerCommand>& input_queue;
    ClientListMonitor& monitor;
    const NPCConfig& npc_config;
    CommonView view;

    void process_commands();
};


#endif
