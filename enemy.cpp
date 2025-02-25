#include <iostream>
#include "enemy.h"
#include "projectile.h"


void enemy::lookForPlayer(std::vector<sf::RectangleShape> terrain, sf::RectangleShape player) {
    std::vector<sf::Vector2f> Offsets;
    Offsets.push_back(sf::Vector2f(0 , -1));
    Offsets.push_back(sf::Vector2f(0 , 1));
    Offsets.push_back(sf::Vector2f(-1 , 0));
    Offsets.push_back(sf::Vector2f(1 , 0));

    //hitboxTexture.loadFromFile("papa.png");
    //hitbox.setTexture(&hitboxTexture);
    //hitbox.setRotation(90.f);

    sf::RectangleShape tmp;
    tmp.setSize(sf::Vector2f(GRIDSIZE , GRIDSIZE));
    tmp.setPosition(hitbox.getPosition());
    tmp.setOrigin(sf::Vector2f(25,25));
    bool terCheck;
    for(int i=0;i<=3;i++)
    {
        terCheck = false;
        for(int j=0;j<=5;j++)
        {
            tmp.move(Offsets[i].x*GRIDSIZE, Offsets[i].y*GRIDSIZE);
            if (i==0){
            }
            for(auto & t : terrain)
            {
                if(tmp.getGlobalBounds().intersects(t.getGlobalBounds()))
                {
                    terCheck = true;
                }
            }
            if(terCheck)
            {
                break;
            }
            if(tmp.getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                   currDirection = directions(i);
                   canSeePlayer = true;
                   return;
            }
        }
        tmp.setPosition(hitbox.getPosition());
}
canSeePlayer = false;
    reactionTime.restart();
}

enemy::enemy(sf::Vector2f pos, int hp, weapons wep) : living_obj(pos, hp, wep) {
    health=hp;
ShootCD = 700;
walkCD = 1000;

//hitbox.setFillColor(sf::Color::Yellow);
}

bool enemy::getCanSeePlayer() {
    return (canSeePlayer && reactionTime.getElapsedTime().asMilliseconds() > 1000);
}

directions enemy::getCurrDirection() {
    return currDirection;
}
