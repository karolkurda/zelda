#ifndef TEMP_LEVEL_H
#define TEMP_LEVEL_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "enemy.h"

class level {
    std::vector<sf::RectangleShape> terrain;
    std::vector<enemy> enemies;

public:
    level();
    std::vector<sf::RectangleShape> getTerrain();
    std::vector<enemy> getEnemies();
    sf::Vector2f getSpawnPosition();

    void getLevel(int lvl);
};



#endif //TEMP_LEVEL_H
