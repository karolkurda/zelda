#include <iostream>
#include "entity.h"
#include "projectile.h"


entity::entity(sf::Vector2f position, int hp) {
    health=hp;
    hp=0;
    hitbox.setPosition(position);
    //hitbox.setFillColor(sf::Color::White);
    hitbox.setSize(sf::Vector2f(50, 50));
    //hitbox.setOrigin(sf::Vector2f(25,25));
    hitbox.setOrigin(sf::Vector2f(hitbox.getSize()/2.f));

}

sf::RectangleShape entity::getHitbox() {
    return hitbox;
}

void entity::moveEntity(directions dir) {

    switch (dir) {
        case UP:
            hitbox.move(sf::Vector2f(0,-GRIDSIZE));
            //hitbox.setRotation(180.f);
            break;
        case DOWN:
            hitbox.move(sf::Vector2f(0,GRIDSIZE));
            //hitbox.setRotation(0.f);
            break;
        case LEFT:
            hitbox.move(sf::Vector2f(-GRIDSIZE,0));
            //hitbox.setRotation(90.f);
            break;
        case RIGHT:
            hitbox.move(sf::Vector2f(GRIDSIZE,0));
            //hitbox.setRotation(270.f);
            break;
        default:
            break;
    }

}

int entity::getHealth() const {
    return health;
}

int entity::takeDMG(int dmg)
{

    if(dmg > 0)
    {
        health-=dmg;
        //std::cout<<"dmg taken"<<std::endl;
    }
    return dmg;
}



void entity::setPosition(float x, float y) {
hitbox.setPosition(x , y);
}

directions entity::getDIR() {
    return dir;
}

