#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "../common_src/command.h"
#include "../common_src/common_view.h"
#include "../common_src/game_event.h"
#include "../common_src/socket.h"

#include "game.h"
#include "server_protocol.h"

/**
 * Server Single Thread just for TESTING PURPOSES
 * crashes when Read n messages is larger than n messages received
 * and "q" from server does not work
 * everything was coded for single thread functioning and then
 * migrated to multi thread
 */
class Server_SS_Test {
private:
    std::string servname;
    NPCConfig npc_config;
    CommonView view;

    void handle_session(ServerProtocol& srv_prot, const std::string& username, Game& game) {

        try {
            while (true) {
                CommandInfo cmd_info = srv_prot.recv_command();

                if (cmd_info.type == Command::DEFEAT) {
                    std::optional<GameEvent> event =
                            game.defeat_npc(username, cmd_info.npc_code.value());

                    if (event.has_value()) {
                        srv_prot.send_event(event.value());
                        view.show_event(event.value(), npc_config);
                    }
                }

                std::vector<GameEvent> appearences = game.run_one_tick();

                for (const GameEvent& event: appearences) {
                    srv_prot.send_event(event);
                    view.show_event(event, npc_config);
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Client disconnected or network error. Ending session.\n";
        }
    }

public:
    explicit Server_SS_Test(const std::string& servname): servname(servname), npc_config() {}

    void run() {
        Socket srv(servname.c_str());
        Socket peer = srv.accept();

        ServerProtocol srv_prot(peer, npc_config);

        std::string username = srv_prot.recv_username();
        Game game(npc_config);

        handle_session(srv_prot, username, game);
    }
};
