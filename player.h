#ifndef ZELDA_PLAYER_H
#define ZELDA_PLAYER_H
#include "entity.h"
#include "living_obj.h"

class player : public living_obj {
sf::Clock swapCooldown;
public:
    int arrowCount;
    player(sf::Vector2f position, int hp, int arrows);
    void swapWeapon();
    sf::Texture linkUpTexture, linkDownTexture, linkLeftTexture, linkRightTexture;


    void swapTextures();

    void sterowanie();
};


#endif //ZELDA_PLAYER_H
