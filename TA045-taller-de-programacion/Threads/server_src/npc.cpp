#include "npc.h"

NPC::NPC(uint8_t ticks_to_respawn):
        alive(true), ticks_to_respawn(ticks_to_respawn), current_ticks(0) {}


bool NPC::is_alive() const { return alive; }

void NPC::kill() {
    alive = false;
    current_ticks = 0;
}

bool NPC::tick() {
    if (alive)
        return false;

    current_ticks++;

    if (current_ticks >= ticks_to_respawn) {
        alive = true;
        return true;
    }

    return false;
}
