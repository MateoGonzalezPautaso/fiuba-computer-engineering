#include "game_loop.h"

#include <chrono>
#include <thread>
#include <vector>

#define SLEEP_MS 200

GameLoop::GameLoop(Queue<PlayerCommand>& input_queue, ClientListMonitor& monitor,
                   const NPCConfig& npc_config):
        game(npc_config),
        input_queue(input_queue),
        monitor(monitor),
        npc_config(npc_config),
        view() {}

void GameLoop::run() {
    try {
        while (should_keep_running()) {
            process_commands();

            std::vector<GameEvent> tick_events = game.run_one_tick();

            for (const auto& event: tick_events) {
                monitor.broadcast(event);
                view.show_event(event, npc_config);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS));
        }
    } catch (const ClosedQueue&) {
        // Nothing to do, normal end of server
    }
}

void GameLoop::process_commands() {
    PlayerCommand player_cmd("", {Command::INVALID, NPCCode::INVALID});

    try {
        while (input_queue.try_pop(player_cmd)) {
            if (player_cmd.info.type == Command::DEFEAT) {
                // auto because return value is std::optional
                auto event = game.defeat_npc(player_cmd.username, player_cmd.info.npc_code.value());

                if (event.has_value()) {
                    monitor.broadcast(event.value());
                    view.show_event(event.value(), npc_config);
                }
            }
        }
    } catch (const ClosedQueue&) {
        // queue is closed -> exit processing commands
    }
}


void GameLoop::stop() {
    Thread::stop();
    input_queue.close();
}
