//
// Created by karol on 6/17/22.
//

#ifndef TEMP_LIVING_OBJ_H
#define TEMP_LIVING_OBJ_H


#include "entity.h"
#include "projectile.h"


enum weapons{sword, bow};
class living_obj : public entity {
protected:
    sf::RectangleShape weapon;
    sf::Clock WalkCooldown;
    sf::Clock ShootCooldown;
    float walkCD;
    float ShootCD;
    weapons currentWeapon;
    directions dir;
public:
    living_obj(sf::Vector2f position, int hp, weapons W);
    directions getDir();

    void walk(directions dir);
    projectile attack(directions DIR);
    weapons getCurrWeapon();
    sf::Time getShootCooldown();

    bool CanShoot();

    float getShootCD();
};


#endif //TEMP_LIVING_OBJ_H
