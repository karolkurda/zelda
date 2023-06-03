#include "level.h"
#include "enemy.h"


level::level() {
    sf::RectangleShape tmp(sf::Vector2f (150 , 50));
    tmp.setPosition(200 , 200);
    terrain.push_back(tmp);
    tmp.setPosition(sf::Vector2f(400 , 200));
    terrain.push_back(tmp);
    enemy e1(sf::Vector2f(150 , 0) , 100 , bow);
    enemy e2(sf::Vector2f(500,200),100, sword);
    enemies.push_back(e1);
    enemies.push_back(e2);
}

std::vector<sf::RectangleShape> level::getTerrain() {
    return terrain;
}

std::vector<enemy> level::getEnemies() {
    return enemies;
}

sf::Vector2f level::getSpawnPosition() {
    return sf::Vector2f();
}

void level::getLevel(int lvl) {
    switch(lvl)
    {
        case 0: {
            terrain.clear();
            enemies.clear();
            sf::RectangleShape tmp(sf::Vector2f(150, 50));
            tmp.setPosition(200, 200);
            terrain.push_back(tmp);
            tmp.setPosition(sf::Vector2f(400, 200));
            terrain.push_back(tmp);
            enemy e1(sf::Vector2f(150, 0), 100, bow);
            enemy e2(sf::Vector2f(500, 200), 100, sword);
            enemies.push_back(e1);
            enemies.push_back(e2);
            return;
        }
        case 1: {
            terrain.clear();
            enemies.clear();
            sf::RectangleShape tmp(sf::Vector2f(50, 50));
            tmp.setPosition(300, 200);
            terrain.push_back(tmp);
            tmp.setPosition(sf::Vector2f(600, 500));
            terrain.push_back(tmp);
            enemy e1(sf::Vector2f(150, 0), 100, bow);
            enemy e2(sf::Vector2f(500, 200), 100, sword);
            enemy e3(sf::Vector2f(500,550), 100, bow);
            enemies.push_back(e1);
            enemies.push_back(e2);
            enemies.push_back(e3);

            return ;


        }
        case 2: {
            terrain.clear();
            enemies.clear();


            return ;
        }
        default:
            return;
    }

}
