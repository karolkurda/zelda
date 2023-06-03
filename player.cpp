#include "player.h"
#include "SFML/Graphics.hpp"

player::player(sf::Vector2f position, int hp) : living_obj(position, hp , bow) {
health = 100;

}
void player::swapWeapon()
{
    if(swapCooldown.getElapsedTime().asMilliseconds() > 1000) {
        if (currentWeapon == sword) {
            currentWeapon = bow;
        } else {
            currentWeapon = sword;
        }
        swapCooldown.restart();
    }
}
