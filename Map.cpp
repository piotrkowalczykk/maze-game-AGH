#include "Map.h"
#include <iostream>
#include "Global.h"

Map::Map(float gridSize) : gridSize(gridSize) {

    pathTexture.loadFromFile(PATH_1);
    wallTexture.loadFromFile(WALL_1);
    enemyTexture.loadFromFile(ENEMY_1);
    pointTexture.loadFromFile(POINT);
    boostTexture.loadFromFile(BOOST);
    buttonTexture.loadFromFile(BUTTON);
    buttonPressedTexture.loadFromFile(BUTTON_PRESSED);
    doorTexture.loadFromFile(DOOR);

}

void Map::draw(sf::RenderWindow& window, const std::vector<std::vector<int>>& map, const std::vector<std::vector<int>>& itemMap) {
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {

            if (map[y][x] == 0) {
                wallSprite.setTexture(pathTexture);
            }
            if (map[y][x] == 1) {
                wallSprite.setTexture(wallTexture);
            }
            if (map[y][x] == 2) {
                wallSprite.setTexture(doorTexture);
                doorPosition = sf::Vector2u(x, y);
            }

            wallSprite.setPosition(x * gridSize, y * gridSize);
            window.draw(wallSprite);

            if (itemMap[y][x] == 0) {
                pointSprite.setTexture(pathTexture);
                boostSprite.setTexture(pathTexture);
                buttonSprite.setTexture(pathTexture);
                buttonSprite.setPosition(x * gridSize, y * gridSize);
                boostSprite.setPosition(x * gridSize, y * gridSize);
                pointSprite.setPosition(x * gridSize, y * gridSize);
            }
            if (itemMap[y][x] == 3) {
                pointSprite.setTexture(pointTexture);
                pointSprite.setPosition(x * gridSize, y * gridSize);
            }
            if (itemMap[y][x] == 4) {
                enemySprite.setTexture(enemyTexture);
                enemySprite.setPosition(x * gridSize, y * gridSize);
            }
            if (itemMap[y][x] == 5) {
                boostSprite.setTexture(boostTexture);
                boostSprite.setPosition(x * gridSize, y * gridSize);
            }
            if (itemMap[y][x] == 6) {
                buttonSprite.setTexture(buttonTexture);
                buttonSprite.setPosition(x * gridSize, y * gridSize);
            }
            if (itemMap[y][x] == 7) {
                buttonSprite.setTexture(buttonPressedTexture);
                buttonSprite.setPosition(x * gridSize, y * gridSize);
            }

            window.draw(pointSprite);
            window.draw(enemySprite);
            window.draw(boostSprite);
            window.draw(buttonSprite);
        }
    }
}

sf::Vector2u Map::getDoorPosition() {
    return doorPosition;
}

void Map::setTextures(const std::string& pathTexture, const std::string& wallTexture, const std::string& enemyTexture){
    this->pathTexture.loadFromFile(pathTexture);
    this->wallTexture.loadFromFile(wallTexture);
    this->enemyTexture.loadFromFile(enemyTexture);
}