#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map(float gridSize);
    void draw(sf::RenderWindow& window, const std::vector<std::vector<int>>& map, const std::vector<std::vector<int>>& itemMap);
    sf::Vector2u getDoorPosition();
    void setTextures(const std::string& pathTexture, const std::string& wallTexture, const std::string& enemyTexture);

private:
    float gridSize;
    sf::Texture pathTexture;
    sf::Texture wallTexture;
    sf::Texture pointTexture;
    sf::Texture enemyTexture;
    sf::Texture boostTexture;
    sf::Texture buttonTexture;
    sf::Texture buttonPressedTexture;
    sf::Texture doorTexture;
    sf::Sprite wallSprite;
    sf::Sprite pointSprite;
    sf::Sprite enemySprite;
    sf::Sprite boostSprite;
    sf::Sprite buttonSprite;
    sf::Vector2u doorPosition;
};

#endif
