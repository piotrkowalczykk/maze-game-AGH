#include "Map.h"
#include <iostream>

Map::Map(float gridSize) : gridSize(gridSize) {
    pathTexture.loadFromFile("textures/path1.png");
    wallTexture.loadFromFile("textures/library.png");
    coinTexture.loadFromFile("textures/plus.png");
    enemyTexture.loadFromFile("textures/enemy1.png");
    boostTexture.loadFromFile("textures/monster.png");
    button1Texture.loadFromFile("textures/button1.png");
    button2Texture.loadFromFile("textures/button2.png");
    doorTexture.loadFromFile("textures/door.png");
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
                coinSprite.setTexture(pathTexture);
                boostSprite.setTexture(pathTexture);
                boostSprite.setPosition(x * gridSize, y * gridSize);
                coinSprite.setPosition(x * gridSize, y * gridSize);
            }
            if (itemMap[y][x] == 3) {
                coinSprite.setTexture(coinTexture);
                coinSprite.setPosition(x * gridSize, y * gridSize);
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
                buttonSprite.setTexture(button2Texture);
                buttonSprite.setPosition(x * gridSize, y * gridSize);
            }
            if (itemMap[y][x] == 7) {
                buttonSprite.setTexture(button1Texture);
                buttonSprite.setPosition(x * gridSize, y * gridSize);
            }

            window.draw(coinSprite);
            window.draw(enemySprite);
            window.draw(boostSprite);
            window.draw(buttonSprite);
        }
    }
}

sf::Vector2u Map::getDoorPosition() {
    return doorPosition;
}