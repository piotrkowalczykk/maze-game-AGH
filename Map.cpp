#include "Map.h"

Map::Map(float gridSize) : gridSize(gridSize) {
    pathTexture.loadFromFile("textures/path1.png");
    wallTexture.loadFromFile("textures/texture2.png");
    wallSprite.setTexture(wallTexture);
}

void Map::draw(sf::RenderWindow& window, const std::vector<std::vector<int>>& map) {
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == 0) {
                wallSprite.setTexture(pathTexture);
            }
            else if (map[y][x] == 1) {
                wallSprite.setTexture(wallTexture);
            }
            wallSprite.setPosition(x * gridSize, y * gridSize);
            window.draw(wallSprite);
        }
    }
}
