#ifndef ZELDA_ENTITY_H
#define ZELDA_ENTITY_H

#define GRIDSIZE 50

#include "SFML/Graphics.hpp"
enum directions {UP = 0 , DOWN = 1, LEFT = 2 , RIGHT = 3};

class entity {

protected:

    sf::RectangleShape hitbox;
    sf::Texture hitboxTexture;
    directions dir;
    directions getDIR();

public:

    int health;
    entity(sf::Vector2f position, int hp);

    sf::RectangleShape getHitbox();

    int getHealth() const;

    int takeDMG(int dmg);

    void moveEntity(directions dir);

    void setPosition (float x, float y);

};


#endif //ZELDA_ENTITY_H
