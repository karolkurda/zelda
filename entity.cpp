#include <iostream>
#include "entity.h"


entity::entity(sf::Vector2f position, int hp) {

    hitbox.setPosition(position);
    hitbox.setFillColor(sf::Color::White);
    hitbox.setSize(sf::Vector2f(50, 50));

}

sf::RectangleShape entity::getHitbox() {
    return hitbox;
}

void entity::moveEntity(directions dir) {

    switch (dir) {
        case UP:
            hitbox.move(sf::Vector2f(0,-GRIDSIZE));
            break;
        case DOWN:
            hitbox.move(sf::Vector2f(0,GRIDSIZE));
            break;
        case LEFT:
            hitbox.move(sf::Vector2f(-GRIDSIZE,0));
            break;
        case RIGHT:
            hitbox.move(sf::Vector2f(GRIDSIZE,0));
            break;
        default:
            break;
    }

}

int entity::getHealth() {
    return health;
}

int entity::takeDMG(int dmg)
{
    health-=dmg;
    if(dmg < 1000)
    {
        std::cout<<"dmg taken"<<std::endl;
    }

}

void entity::setPosition(float x, float y) {
hitbox.setPosition(x , y);
}


