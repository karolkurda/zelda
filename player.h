#ifndef ZELDA_PLAYER_H
#define ZELDA_PLAYER_H
#include "entity.h"
#include "living_obj.h"

class player : public living_obj {
sf::Clock swapCooldown;
public:
    player(sf::Vector2f position, int hp);
    void swapWeapon();


};


#endif //ZELDA_PLAYER_H
