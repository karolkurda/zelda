#include <iostream>
#include "game.h"
#include "enemy.h"
#include "level.h"
#include <SFML/Graphics.hpp>

    game::game(player P , sf::RenderWindow & win) : lunk(P) , window(win) {
    heart.setSize(sf::Vector2f(50 , 50));
    drawBow.setSize(sf::Vector2f(50 , 50));
    drawSword.setSize(sf::Vector2f(50 , 50));


    levels.getLevel(0);
    currLevel = 0;

    terrain = levels.getTerrain();
    enemies = levels.getEnemies();
    passages = levels.getPassages();
    passageState = levels.canGoNext();
    podlogaVect = levels.getPodloga();

    Offsets.push_back(sf::Vector2f(0 , -1));
    Offsets.push_back(sf::Vector2f(0 , 1));
    Offsets.push_back(sf::Vector2f(-1 , 0));
    Offsets.push_back(sf::Vector2f(1 , 0));
    std::cout<<terrain.size();
    std::cout<<enemies.size();

    swordTexture.loadFromFile("items.png", sf::IntRect(280,120,20,20));
    drawSword.setTexture(&swordTexture);

    bowTexture.loadFromFile("items.png", sf::IntRect(320,0,20,20));
    drawBow.setTexture(&bowTexture);

    heartTexture.loadFromFile("items.png", sf::IntRect(240,40,15,15));
    heart.setTexture(&heartTexture);



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
        window.draw(podlogaVect[0]);
        window.draw(lunk.getHitbox());
        if(gameCLOCK.getElapsedTime().asMilliseconds() > 70)
        {

            //std::cout<<enemies.size(); //to bedzie dobre do ogarniecia ile zostalo przeciwnikow
            gameCLOCK.restart();
        }
        //SwapLevels();
        drawHud();
        lunk.sterowanie();
        DrawProj();
        UpdateProjectiles();
        didHit();
        wallHit();
        UpdateEnemies();
        UpdateWalls();

        canGo();

        if (passageState){SwapLevels();}
        window.draw(passages[0]);
        window.draw(passages[1]);
        //std::cout<<"zdrowie: "<<lunk.health<<std::endl;

        window.display();
    }


}

void game::control()
{

sf::RectangleShape tmp(sf::Vector2f(50 , 50));
tmp.setPosition(lunk.getHitbox().getPosition());
tmp.setOrigin(sf::Vector2f(25,25));

if((lunk.getShootCooldown().asMilliseconds() > lunk.getShootCD()/2))
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

        tmp.move(sf::Vector2f(0, -GRIDSIZE));
        if(wallCheck(tmp)) {
            lunk.walk(UP);
            lunk.swapTextures();
            return;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

        tmp.move(sf::Vector2f(0 , GRIDSIZE));
        if(wallCheck(tmp)) {
            lunk.walk(DOWN);
            lunk.swapTextures();
            return;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        tmp.move(sf::Vector2f(-GRIDSIZE , 0));
        if(wallCheck(tmp)) {
            lunk.walk(LEFT);
            lunk.swapTextures();
            return;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

        tmp.move(sf::Vector2f(GRIDSIZE , 0));
        if(wallCheck(tmp)) {
            lunk.walk(RIGHT);
            lunk.swapTextures();
            return;
        }
    }
}

    if(lunk.getShootCooldown().asMilliseconds() > lunk.getShootCD()) {


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (lunk.getCurrWeapon() != bow || lunk.arrowCount > 0)) {
            Projectiles.push_back(lunk.attack(UP));
            if (lunk.getCurrWeapon() == bow) lunk.arrowCount -= 1;
            std::cout << "arrows: " << lunk.arrowCount << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (lunk.getCurrWeapon() != bow || lunk.arrowCount > 0)) {
            Projectiles.push_back(lunk.attack(DOWN));
            if (lunk.getCurrWeapon() == bow) lunk.arrowCount -= 1;
            std::cout << "arrows: " << lunk.arrowCount << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (lunk.getCurrWeapon() != bow || lunk.arrowCount > 0)) {
            Projectiles.push_back(lunk.attack(LEFT));
            if (lunk.getCurrWeapon() == bow) lunk.arrowCount -= 1;
            std::cout << "arrows: " << lunk.arrowCount << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (lunk.getCurrWeapon() != bow || lunk.arrowCount > 0)) {
            Projectiles.push_back(lunk.attack(RIGHT));
            if (lunk.getCurrWeapon() == bow) lunk.arrowCount -= 1;
            std::cout << "arrows: " << lunk.arrowCount << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) lunk.swapWeapon();
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
    for(int p=0;p<Projectiles.size();p++)
    {
        window.draw(Projectiles[p].getHitbox());
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

            if(enemies[e].getShootCooldown().asMilliseconds() > enemies[e].getShootCD()/2) {
            tmp.move(GRIDSIZE*Offsets[enemies[e].getCurrDirection()].x , GRIDSIZE*Offsets[enemies[e].getCurrDirection()].y);
            if(wallCheck(tmp)) {
                enemies[e].walk(enemies[e].getCurrDirection());
            }
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
    if(lunk.getHitbox().getGlobalBounds().intersects(passages[0].getGlobalBounds()))
    {
        if(currLevel > 0) {
            //std::cout<<"prev";
            levels.getLevel(currLevel - 1);
            currLevel = currLevel - 1;
            terrain = levels.getTerrain();
            enemies = levels.getEnemies();
            lunk.setPosition(700+25, lunk.getHitbox().getPosition().y);
            passageState=0;
        }
    }
    if(lunk.getHitbox().getGlobalBounds().intersects(passages[1].getGlobalBounds()))
    {
        if(currLevel < 4) {
            //std::cout<<"next";
            levels.getLevel(currLevel + 1);
            currLevel = currLevel + 1;
            terrain = levels.getTerrain();
            enemies = levels.getEnemies();
            lunk.setPosition(50+25, lunk.getHitbox().getPosition().y);
            passageState=0;
        }
    }
}
void game::wallHit() {
    for (int w = 0; w < terrain.size(); w++) {
        for (int p = 0; p < Projectiles.size(); p++) {
            if (Projectiles[p].getHitbox().getGlobalBounds().intersects(terrain[w].getGlobalBounds()))
            {
                Projectiles[p].health=0;
            }
        }
    }
}

//void game::enemyWantsToEscape()
//{
//    for (int w = 0; w < terrain.size(); w++) {
//        for (int e = 0; e < enemies.size(); e++) {
//            if(enemies[e].getHitbox().getGlobalBounds().intersects(terrain[w].getGlobalBounds()))
//            {
//
//            }
//        }
//    }
//}

void game::didHit() {
    for (int p = 0; p < Projectiles.size(); p++) {
        if(Projectiles[p].getHitbox().getGlobalBounds().intersects(lunk.getHitbox().getGlobalBounds())){
            lunk.takeDMG(Projectiles[p].getHealth());
            Projectiles[p].health = 0;
        }
        for (int e = 0; e < enemies.size(); e++) {
            if (Projectiles[p].getHitbox().getGlobalBounds().intersects(enemies[e].getHitbox().getGlobalBounds())) {
                enemies[e].takeDMG(Projectiles[p].getHealth());
                std::cout << Projectiles[p].getHealth();
                Projectiles[p].health = 0;
            }
        }

    }
}

void game::HealthCheck()
{
    if(!Projectiles.empty())
    {
        for(int p=0;p<Projectiles.size();p++)
        {

            if(Projectiles[p].getHealth() <= 0)
            {
                //std::cout<<"projectile erased";
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

    if (lunk.getCurrWeapon() == sword){
        drawSword.setPosition(700 , 615);
        window.draw(drawSword);
    }
    else if (lunk.getCurrWeapon() == bow)
    {
        drawBow.setPosition(700 , 615);
        window.draw(drawBow);
    }

    for (int i = 0; i <= lunk.getHealth()/10; i++)
    {
        heart.setPosition(0 + (i * heart.getSize().x) + 10 * i , 615 );
        window.draw(heart);
    }

}

void game::lunkDied() {

    std::cout<<"resetlunkdied"<<std::endl;
    window.draw(gameOverScreen);
    sf::Clock deathTimer;
    levels.getLevel(0);
    currLevel = 0;
    terrain = levels.getTerrain();
    enemies = levels.getEnemies();
    lunk.setPosition(225, 425);
    lunk.health = 50;
    lunk.arrowCount = 20;

  //  playerProjectiles.clear();

}

void game::canGo(){
    if(enemies.size()==0) passageState =1;
}