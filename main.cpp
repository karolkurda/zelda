#include <iostream>
#include "SFML/Graphics.hpp"
#include "entity.h"
#include "player.h"
#include "projectile.h"
#include "game.h"
int main() {

    srand(time(0));
    player p1(sf::Vector2f(300 , 300), 50);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Zelda");
    game g1(p1,window);
    g1.Loop();


    return 0;
}