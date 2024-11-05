#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map(float gridSize);
    void draw(sf::RenderWindow& window, const std::vector<std::vector<int>>& map);

private:
    float gridSize;
    sf::Texture pathTexture;
    sf::Texture wallTexture;
    sf::Sprite wallSprite;
};

#endif
