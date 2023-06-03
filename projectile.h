//
// Created by karol on 6/17/22.
//

#ifndef TEMP_PROJECTILE_H
#define TEMP_PROJECTILE_H


#include "entity.h"

class projectile : public entity {
    std::vector<projectile> Projectiles;

directions currDIR;
int time;
sf::Texture arrow;

public:
    sf::Clock projectileSpeed;
    sf::Clock projectileTTL;
    projectile(sf::Vector2f POS, directions dir, int dmg,int t);
    void Update();
};


#endif //TEMP_PROJECTILE_H
