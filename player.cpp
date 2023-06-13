#include "player.h"
#include "SFML/Graphics.hpp"
#include <iostream>

player::player(sf::Vector2f position, int hp, int arrows) : living_obj(position, hp , bow) {
    health = 0;
    arrowCount = arrows;
    linkUpTexture.loadFromFile("link.png", sf::IntRect(58,0,20,20));
    linkDownTexture.loadFromFile("link.png", sf::IntRect(0,0,20,20));
    linkLeftTexture.loadFromFile("link.png", sf::IntRect(28,0,20,20));
    linkRightTexture.loadFromFile("link.png", sf::IntRect(88,0,20,20));
    hitbox.setTexture(&linkDownTexture);

}
void player::swapWeapon()
{
    if(swapCooldown.getElapsedTime().asMilliseconds() > 1000) {
        if (currentWeapon == sword) {
            currentWeapon = bow;
            std::cout<<"swapped to bow\n";
        } else {
            currentWeapon = sword;
            std::cout<<"swapped to sword\n";
        }
        swapCooldown.restart();
    }
}

void player::sterowanie()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {dir=UP;}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {dir=DOWN;}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {dir=LEFT;}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {dir=RIGHT;}
}


//void player::swapTextures(){
//    switch (dir) {
//        case UP:
//            hitboxTexture.loadFromFile("link.png", sf::IntRect(28,0,20,20));
//            hitbox.setTexture(&hitboxTexture);
//            std::cout<<"swapped";
//            break;
//        case DOWN:
//            hitboxTexture.loadFromFile("link.png", sf::IntRect(0,0,20,20));
//            hitbox.setTexture(&hitboxTexture);
//            break;
//        case LEFT:
//            hitboxTexture.loadFromFile("link.png", sf::IntRect(28,0,20,20));
//            hitbox.setTexture(&hitboxTexture);
//            break;
//        case RIGHT:
//            hitboxTexture.loadFromFile("link.png", sf::IntRect(88,0,20,20));
//            hitbox.setTexture(&hitboxTexture);
//            break;
//        default:
//            break;
//    }
//}


void player::swapTextures(){

    if (getDir()==UP){
            hitbox.setTexture(&linkUpTexture);}

    if (getDir()==DOWN){
            hitbox.setTexture(&linkDownTexture);}

    if (getDir()==LEFT){
            hitbox.setTexture(&linkLeftTexture);}

    if (getDir()==RIGHT){
            hitbox.setTexture(&linkRightTexture);}
    }

