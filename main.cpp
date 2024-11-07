#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Global.h"
#include "GUI.h"
#include "Menu.h"
#include <iostream>
#include <string>

void changeMap(std::vector<std::vector<int>>& currentMap,
    std::vector<std::vector<int>>& currentMapReseter,
    std::vector<std::vector<int>>& currentMapItems,
    std::vector<std::vector<int>>& currentMapItemsReseter,
    std::vector<std::vector<int>> nextMap,
    std::vector<std::vector<int>> nextMapItems)
{
    currentMap = nextMap;
    currentMapReseter = nextMap;
    currentMapItems = nextMapItems;
    currentMapItemsReseter = nextMapItems;
}

int main() {

    // Game

    sf::Clock dt_clock;
    float deltaTime;

    // Window

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);
    window.setFramerateLimit(FRAMERATE_LIMIT);

    // Menu

    Menu menu;
    bool startGame = false;

    // Player

    Player player;
    sf::View view = window.getDefaultView();

    // Map

    Map map(GRID_SIZE);
    int currentLevel = 1;
    std::string currentLevelName = "Analiza Matematyczna";

    std::vector<std::vector<int>> currentMap;
    std::vector<std::vector<int>> currentMapItems;
    std::vector<std::vector<int>> currentMapReseter;
    std::vector<std::vector<int>> currentMapItemsReseter;

    currentMap = MAP_1;
    currentMapReseter = MAP_1;
    currentMapItems = MAP_1_ITEMS;
    currentMapItemsReseter = MAP_1_ITEMS;

    // GUI

    sf::Font font;
    if (!font.loadFromFile("fonts/font.ttf")) {
        std::cout << "Error";
        return -1;
    }

    int points = 0;

    sf::Text pointsText;
    GUI gui(font);
    gui.update(points, currentLevelName);
    gui.setPosition(view);
    


    while (window.isOpen()) {
        deltaTime = dt_clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (!startGame) {
                menu.handleInput(event, startGame);
            }
        }

        if (startGame) {

            player.handleInput(deltaTime);
            for (size_t y = 0; y < currentMap.size(); ++y) {
                for (size_t x = 0; x < currentMap[y].size(); ++x) {

                    // Collision

                    if (currentMap[y][x] == 1 || currentMap[y][x] == 2) {
                        sf::FloatRect wallBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                        player.resolveCollision(wallBounds);
                    }

                    // Point 

                    if (currentMapItems[y][x] == 3) {
                        sf::FloatRect pointBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                        if (player.checkItemCollision(pointBounds)) {
                            currentMapItems[y][x] = 0;
                            points++;
                        }
                    }

                    // Enemy

                    if (currentMapItems[y][x] == 4) {
                        sf::FloatRect enemyBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                        if (player.checkItemCollision(enemyBounds)) {
                            points = 0;
                            player.setMovementBoost(1.0f);
                            player.setPosition(140, 136);
                            currentMapItems = currentMapItemsReseter;
                            currentMap = currentMapReseter;
                        }
                    }

                    // Boost

                    if (currentMapItems[y][x] == 5) {
                        sf::FloatRect boostBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                        if (player.checkItemCollision(boostBounds)) {
                            currentMapItems[y][x] = 0;
                            player.setMovementBoost(4.0f);
                        }
                    }

                    // Button

                    if (currentMapItems[y][x] == 6) {
                        sf::FloatRect doorBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                        if (player.checkItemCollision(doorBounds)) {
                            currentMapItems[y][x] = 7;
                            currentMap[map.getDoorPosition().y][map.getDoorPosition().x] = 0;
                        }
                    }
                }
            }

            // Change level

            if (player.getPosition().x > 1300 && player.getPosition().y > 950) {
                ++currentLevel;
                switch (currentLevel) {
                case (2):
                    changeMap(currentMap, currentMapReseter, currentMapItems, currentMapItemsReseter, MAP_2, MAP_2_ITEMS);
                    map.setTextures(PATH_2, WALL_2, ENEMY_2);
                    currentLevelName = "Algebra";
                    player.setMovementBoost(1.0f);
                    break;
                case (3):
                    changeMap(currentMap, currentMapReseter, currentMapItems, currentMapItemsReseter, MAP_3, MAP_3_ITEMS);
                    map.setTextures(PATH_3, WALL_3, ENEMY_3);
                    currentLevelName = "Procesy wytwarzania metali...";
                    player.setMovementBoost(1.0f);
                    break;
                }
                player.setPosition(138, 136);
            }

            player.move();
            view.setCenter(player.getPosition());
            window.setView(view);
            gui.setPosition(view);

            window.clear(sf::Color::Black);
            map.draw(window, currentMap, currentMapItems);
            player.draw(window);
            gui.update(points, currentLevelName);
            gui.draw(window);
            window.display();

        }
        else {

            window.clear(sf::Color::Green);
            menu.draw(window);
            window.display();

        }
    }

    return 0;
}
