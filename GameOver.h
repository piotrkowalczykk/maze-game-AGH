#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Graphics.hpp>

class GameOver {
public:
    GameOver();
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event& event, bool& endGame, bool& startGame);
    bool buttonHovered;
    void setPoints(int points);

private:
    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Sprite menuButton;
    sf::Font font;
    sf::Texture menuButtonTexture1;
    sf::Texture menuButtonTexture2;
    int points;
};

#endif
