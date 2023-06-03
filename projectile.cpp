//
// Created by karol on 6/17/22.
//

#include "projectile.h"





void projectile::Update() {
    moveEntity(currDIR);
    time -=1;
    if(time < 1)
    {
        takeDMG(1000);
    }
}

projectile::projectile(sf::Vector2f POS, directions dir, int dmg, int t) : entity(POS , dmg){
    currDIR = dir;
    time = t;
    hitbox.setSize(sf::Vector2f(45 , 45));
    hitbox.setFillColor(sf::Color::Red);


}

