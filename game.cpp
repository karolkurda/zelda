#include <iostream>
#include "game.h"
#include "enemy.h"
#include <SFML/Graphics.hpp>

    game::game(player P , sf::RenderWindow & win) : lunk(P) , window(win) {
    heart.setSize(sf::Vector2f(50 , 50));
    drawBow.setSize(sf::Vector2f(50 , 50));
    drawSword.setSize(sf::Vector2f(50 , 50));
    drawSword.setPosition(700 , 50);
    drawBow.setPosition(700 , 50);
    levels.getLevel(0);
    currLevel = 0;
    sf::RectangleShape tmp(sf::Vector2f (GRIDSIZE , window.getSize().y));
    terrain = levels.getTerrain();
    enemies = levels.getEnemies();
    tmp.setPosition(0, 0);
    nextLevel.push_back(tmp);
    tmp.setPosition(800 , 0);
    nextLevel.push_back(tmp);
    Offsets.push_back(sf::Vector2f(0 , -1));
    Offsets.push_back(sf::Vector2f(0 , 1));
    Offsets.push_back(sf::Vector2f(-1 , 0));
    Offsets.push_back(sf::Vector2f(1 , 0));
    std::cout<<terrain.size();
    std::cout<<enemies.size();
    swordTexture.loadFromFile("textures/sword.png");
    bowTexture.loadFromFile("textures/bow.png");
    heartTexture.loadFromFile("textures/heart.png");

}
void game::Loop() {

    gameCLOCK.restart();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
     HealthCheck();
        control();
        window.clear();

        window.draw(lunk.getHitbox());
        if(gameCLOCK.getElapsedTime().asMilliseconds() > 70)
        {
            UpdateProjectiles();
            gameCLOCK.restart();
        }
        DrawProj();
        UpdateEnemies();
        UpdateWalls();
        SwapLevels();
        window.draw(nextLevel[0]);
        window.draw(nextLevel[1]);
        window.display();
    }


}

void game::control()
{
sf::RectangleShape tmp(sf::Vector2f(50 , 50));
tmp.setPosition(lunk.getHitbox().getPosition());
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

        tmp.move(sf::Vector2f(0, -GRIDSIZE));
        if(wallCheck(tmp)) {
            lunk.walk(UP);
            return;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

        tmp.move(sf::Vector2f(0 , GRIDSIZE));
        if(wallCheck(tmp)) {
            lunk.walk(DOWN);
            return;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        tmp.move(sf::Vector2f(-GRIDSIZE , 0));
        if(wallCheck(tmp)) {
            lunk.walk(LEFT);
            return;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

        tmp.move(sf::Vector2f(GRIDSIZE , 0));
        if(wallCheck(tmp)) {
            lunk.walk(RIGHT);
            return;
        }
    }
    if(lunk.getShootCooldown().asMilliseconds() > lunk.getShootCD()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Projectiles.push_back(lunk.attack(UP));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Projectiles.push_back(lunk.attack(DOWN));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) Projectiles.push_back(lunk.attack(LEFT));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Projectiles.push_back(lunk.attack(RIGHT));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) lunk.swapWeapon();

}
}
void game::UpdateProjectiles() {
    if(!Projectiles.empty())
    {
        for(int p=0;p<Projectiles.size();p++)
        {
            Projectiles[p].Update();
        }
    }
}
void game::DrawProj() {
if(!Projectiles.empty())
{
    for(int p=0;p<Projectiles.size();p++)
    {
        window.draw(Projectiles[p].getHitbox());
    }
}


}
void game::UpdateEnemies()
{

    sf::RectangleShape tmp(sf::Vector2f(GRIDSIZE, GRIDSIZE));

    for(int e=0;e<enemies.size();e++)
    {
        tmp.setPosition(enemies[e].getHitbox().getPosition());
        if( enemies[e].getCanSeePlayer() )
        {
            if(enemies[e].CanShoot())
            {
                Projectiles.push_back(enemies[e].attack(enemies[e].getCurrDirection()));
            }
            tmp.move(GRIDSIZE*Offsets[enemies[e].getCurrDirection()].x , GRIDSIZE*Offsets[enemies[e].getCurrDirection()].y);
            if(wallCheck(tmp)) {
                enemies[e].walk(enemies[e].getCurrDirection());
            }
        }

    else
    {
        int wdir = rand() & 3;
        tmp.move(GRIDSIZE*Offsets[wdir].x , GRIDSIZE*Offsets[wdir].y);
        if(wallCheck(tmp))
        {
            enemies[e].walk(directions(wdir));
        }
    }
        enemies[e].lookForPlayer( terrain,lunk.getHitbox());
        window.draw(enemies[e].getHitbox());
    }
}
void game::UpdateWalls()
{
    for(const auto & i : terrain)
    {
       window.draw(i);
    }
}
bool game::wallCheck(sf::RectangleShape tmp)
{
    for(int w=0;w<terrain.size();w++)
    {
        if(terrain[w].getGlobalBounds().intersects(tmp.getGlobalBounds()))
        {
            return false;
        }
    }
    return true;
}
void game::SwapLevels()
{
    if(lunk.getHitbox().getGlobalBounds().intersects(nextLevel[0].getGlobalBounds()))
    {
        if(currLevel > 0) {

            levels.getLevel(currLevel - 1);
            currLevel = currLevel - 1;
            terrain = levels.getTerrain();
            enemies = levels.getEnemies();
            lunk.setPosition(750, lunk.getHitbox().getPosition().y);
        }
    }
    if(lunk.getHitbox().getGlobalBounds().intersects(nextLevel[1].getGlobalBounds()))
    {
        if(currLevel < 4) {

            levels.getLevel(currLevel + 1);
            currLevel = currLevel + 1;
            terrain = levels.getTerrain();
            enemies = levels.getEnemies();
            lunk.setPosition(50, lunk.getHitbox().getPosition().y);
        }
    }
}
void game::HealthCheck()
{
    if(!Projectiles.empty())
    {
        for(int p=0;p<Projectiles.size();p++)
        {
            if(Projectiles[p].getHealth() < 1)
            {
                Projectiles.erase(Projectiles.begin() + p);
            }
        }
    }
        if(!enemies.empty()) {
            for (int e = 0; e < enemies.size(); e++) {
                if (enemies[e].getHealth() < 1) {
                    enemies.erase(enemies.begin() + e);
                }
            }
        }

        if(lunk.getHealth()<1)
        {
         lunkDied();
        }
}


void game::drawHud() {

    switch (lunk.getCurrWeapon()) {

        case sword:
            window.draw(drawSword);
            break;
        case bow:
            window.draw(drawBow);
            break;
    }
    for (int i = 0; i < lunk.getHealth(); i++)
    {
        heart.setPosition(800 - (i * heart.getSize().x) - 10 * i , 500 );
        window.draw(heart);
    }

}

void game::lunkDied() {

    std::cout<<"resetlunkdied"<<std::endl;
    window.draw(gameOverScreen);
    sf::Clock deathTimer;
    while (deathTimer.getElapsedTime().asMicroseconds() < 3000) {}

  //  playerProjectiles.clear();
    levels.getLevel(0);
    currLevel = 0;
    terrain = levels.getTerrain();
    enemies = levels.getEnemies();
    lunk.setPosition(50, lunk.getHitbox().getPosition().y);
}
