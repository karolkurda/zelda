#include "player.h"
#include "SFML/Graphics.hpp"
#include <iostream>

player::player(sf::Vector2f position, int hp) : living_obj(position, hp , bow) {
health = 0;

}
void player::swapWeapon()
{
    if(swapCooldown.getElapsedTime().asMilliseconds() > 1000) {
        if (currentWeapon == sword) {
            currentWeapon = bow;
            std::cout<<"swapped to bow\n";
        } else {
            currentWeapon = sword;
            std::cout<<"swapped to sword\n";
        }
        swapCooldown.restart();
    }
}
