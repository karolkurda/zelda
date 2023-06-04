#ifndef TEMP_LEVEL_H
#define TEMP_LEVEL_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "enemy.h"


class level{
    std::vector<sf::RectangleShape> terrain;
    std::vector<enemy> enemies;
    std::vector<sf::RectangleShape> passages;
    bool passageState;
public:
    level();
    std::vector<sf::RectangleShape> getTerrain();
    std::vector<enemy> getEnemies();
    sf::Vector2f getSpawnPosition();

    void getLevel(int lvl);

    void setBounds();

    void setPassages();

    std::vector<sf::RectangleShape> getPassages();

    void removeBounds();

    bool canGoNext();
};



#endif //TEMP_LEVEL_H
