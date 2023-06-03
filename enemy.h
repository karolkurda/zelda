#ifndef TEMP_ENEMY_H
#define TEMP_ENEMY_H
#include "living_obj.h"


class enemy : public living_obj{


    directions currDirection;
    bool canSeePlayer;
    sf::Clock reactionTime;

public:
    enemy(sf::Vector2f pos , int hp , weapons wep);
    void lookForPlayer(std::vector<sf::RectangleShape> terrain, sf::RectangleShape player);
    directions getCurrDirection();
    bool getCanSeePlayer();

};


#endif //TEMP_ENEMY_H
