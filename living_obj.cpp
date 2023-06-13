#include "living_obj.h"


void living_obj::walk(directions dir) {
    if(WalkCooldown.getElapsedTime().asMilliseconds() > walkCD)
    {
        entity::moveEntity(dir);
        WalkCooldown.restart();
    }


}

living_obj::living_obj(sf::Vector2f position, int hp, weapons W) : entity(position , hp) {
walkCD = 200;
currentWeapon = W;
ShootCD = 500;

}

projectile living_obj::attack(directions DIR) {
sf::Vector2f tmp;

        switch (DIR) {

            case UP:
                tmp = sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().y - (GRIDSIZE + 5));
                break;
            case DOWN:
                tmp = sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().y + (GRIDSIZE+ 5));
                break;
            case LEFT:
                tmp = sf::Vector2f(hitbox.getPosition().x - (GRIDSIZE + 5), hitbox.getPosition().y);
                break;
            case RIGHT:
                tmp = sf::Vector2f(hitbox.getPosition().x + (GRIDSIZE + 5), hitbox.getPosition().y);
                break;

        }

        switch (currentWeapon) {
            case sword:
                ShootCooldown.restart();

                return {tmp, DIR, 20, 1};
            case bow:
                ShootCooldown.restart();

                return {tmp, DIR, 10, 6};
        }
}



sf::Time living_obj::getShootCooldown()
{
    return ShootCooldown.getElapsedTime();
}

float living_obj::getShootCD(){
    return ShootCD;
}

bool living_obj::CanShoot() {
    return (ShootCooldown.getElapsedTime().asMilliseconds() > ShootCD*1.5);
}

weapons living_obj::getCurrWeapon() {
    return currentWeapon;
}
