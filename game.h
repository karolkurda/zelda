#ifndef TEMP_GAME_H
#define TEMP_GAME_H
#include "projectile.h"
#include "player.h"
#include "enemy.h"
#include "level.h"

class game {
    sf::Clock gameCLOCK;

    std::vector<projectile> Projectiles;
    std::vector<enemy> enemies;
    std::vector<sf::RectangleShape> terrain;
    player lunk;
    sf::RenderWindow & window;
    std::vector<sf::Vector2f> Offsets;
    level levels;
    std::vector<sf::RectangleShape> nextLevel;
    int currLevel;
    sf::RectangleShape heart;
    sf::RectangleShape drawBow;
    sf::RectangleShape drawSword;
    sf::RectangleShape gameOverScreen;
    sf::Texture swordTexture, bowTexture, heartTexture;


public:
    void drawHud();
    game(player P , sf::RenderWindow & win);
    void Loop();

    void control();

    void UpdateProjectiles();

    void DrawProj();

    void UpdateEnemies();


    void lunkDied();

    void UpdateWalls();

    bool wallCheck(sf::RectangleShape tmp);

    void SwapLevels();

    void HealthCheck();
};


#endif //TEMP_GAME_H
