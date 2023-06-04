#include <iostream>
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
    passageState=false;
    std::cout<<"otwarte czy zamkniete: "<<passageState<<std::endl;
}
void level::setBounds(){
    sf::RectangleShape upperBound(sf::Vector2f(800,1));
    upperBound.setFillColor(sf::Color::Green);
    upperBound.setPosition(0,-10);
    terrain.push_back(upperBound);

    sf::RectangleShape lowerBound(sf::Vector2f(800,1));
    lowerBound.setFillColor(sf::Color::Green);
    lowerBound.setPosition(0,600);
    terrain.push_back(lowerBound);

    sf::RectangleShape leftBound(sf::Vector2f(1,600));
    leftBound.setFillColor(sf::Color::Green);
    leftBound.setPosition(-10,0);
    terrain.push_back(leftBound);

    sf::RectangleShape rightBound(sf::Vector2f(1,600));
    rightBound.setFillColor(sf::Color::Green);
    rightBound.setPosition(800,0);
    terrain.push_back(rightBound);
}

void level::setPassages(){
    sf::RectangleShape tmp(sf::Vector2f (1 , 600));
    tmp.setPosition(1, 0);
    passages.push_back(tmp);
    tmp.setPosition(799 , 0);
    passages.push_back(tmp);
}



bool level::canGoNext(){
    if (getEnemies().size() == 0) passageState = true;
    std::cout<<"stan przejscia"<<passageState;
    return passageState;
}

//bool level::isPassageOpen() const{
//    return passageState;
//}

//void level::removeBounds(){
//    if (passageState){
//        std::cout<<"otwarte\n";
//        terrain.erase(terrain.end());
//        terrain.erase(terrain.end());
//    }
//}

void level::removeBounds(){
    if (passageState){
        std::cout<<"otwarte\n";
        setPassages();
    }
}

std::vector<sf::RectangleShape> level::getPassages(){
    return passages;
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

            setBounds();

            //isPassageOpen();


            sf::RectangleShape tmp(sf::Vector2f(150, 50));


            tmp.setPosition(200, 200);
            terrain.push_back(tmp);
            tmp.setPosition(sf::Vector2f(400, 200));
            terrain.push_back(tmp);
            enemy e1(sf::Vector2f(150, 100), 100, bow);
            enemy e2(sf::Vector2f(500, 200), 100, sword);
            enemies.push_back(e1);
            enemies.push_back(e2);
            setPassages();
            canGoNext();
            removeBounds();

            return;
        }
        case 1: {
            terrain.clear();
            enemies.clear();
            setBounds();
            setPassages();
            canGoNext();
            removeBounds();
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
            setBounds();


            return ;
        }
        default:
            return;
    }

}
