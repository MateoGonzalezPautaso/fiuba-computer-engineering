#ifndef NPC_H
#define NPC_H

#include <cstdint>

class NPC {
public:
    explicit NPC(uint8_t ticks_to_respawn);

    bool is_alive() const;

    void kill();
    bool tick();  // returns true if NPC needs to respawn

private:
    bool alive;
    uint8_t ticks_to_respawn;
    uint8_t current_ticks;
};

#endif
