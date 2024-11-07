#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map(float gridSize);
    void draw(sf::RenderWindow& window, const std::vector<std::vector<int>>& map, const std::vector<std::vector<int>>& itemMap);
    sf::Vector2u getDoorPosition();

private:
    float gridSize;
    sf::Texture pathTexture;
    sf::Texture wallTexture;
    sf::Texture coinTexture;
    sf::Texture enemyTexture;
    sf::Texture boostTexture;
    sf::Texture button1Texture;
    sf::Texture button2Texture;
    sf::Texture doorTexture;
    sf::Sprite wallSprite;
    sf::Sprite coinSprite;
    sf::Sprite enemySprite;
    sf::Sprite boostSprite;
    sf::Sprite buttonSprite;
    sf::Vector2u doorPosition;
};

#endif
