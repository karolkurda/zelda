//
// Created by karol on 6/17/22.
//

#include "projectile.h"
#include <iostream>





void projectile::Update() {

    if(projectileSpeed.getElapsedTime().asMilliseconds() > 150)
    {
        time=time-1;
        moveEntity(currDIR);
        projectileSpeed.restart();
        if(time == 0) {
            takeDMG(100);
        }
    }
}



projectile::projectile(sf::Vector2f POS, directions dir, int dmg, int t) : entity(POS , dmg){
    currDIR = dir;
    time = t;
    health=dmg;
    hitbox.setSize(sf::Vector2f(20 , 20));
    hitbox.setOrigin(sf::Vector2f(10,10));

    hitbox.setFillColor(sf::Color::Red);
}

