#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Global.h"
#include "GUI.h"
#include "Menu.h"
#include <iostream>
#include <string>


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

    std::vector<std::vector<int>> currentMap;
    std::vector<std::vector<int>> currentMapItems;
    Map map(GRID_SIZE);
    int currentLevel = 1;
    std::string currentLevelName = "Analiza Matematyczna";
    currentMap = MAP1;
    currentMapItems = MAP1_ITEMS;

    // UI
    sf::Font font;
    if (!font.loadFromFile("fonts/font.ttf")) {
        std::cerr << "Nie uda³o siê za³adowaæ czcionki!" << std::endl;
        return -1;
    }
    sf::Text coinText;
    GUI gui(font);
    int coins = 0;
    gui.update(coins, currentLevelName);
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

            // Collision

            player.handleInput(deltaTime);
            for (size_t y = 0; y < currentMap.size(); ++y) {
                for (size_t x = 0; x < currentMap[y].size(); ++x) {
                    if (currentMap[y][x] == 1) {
                        sf::FloatRect wallBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                        player.resolveCollision(wallBounds);
                    }
                    if (currentMapItems[y][x] == 3) {
                        sf::FloatRect coinBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                        if (player.checkItemCollision(coinBounds)) {
                            std::cout << "coin";
                            currentMapItems[y][x] = 0;
                            coins++;
                        }
                    }
                    if (currentMapItems[y][x] == 4) {
                        sf::FloatRect enemyBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                        if (player.checkItemCollision(enemyBounds)) {
                            coins = 0;
                            player.setMovementBoost(1.0f);
                            player.setPosition(140, 136);
                            currentMapItems = MAP1_ITEMS;
                        }
                    }
                    if (currentMapItems[y][x] == 5) {
                        sf::FloatRect boostBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                        if (player.checkItemCollision(boostBounds)) {
                            std::cout << "boost";
                            currentMapItems[y][x] = 0;
                            player.setMovementBoost(2.0f);
                        }
                    }
                }
            }

            // Change lvl

            if (player.getPosition().x > 1300 && player.getPosition().y > 950) {
                
                switch (currentLevel) {
                case (1):
                    currentMap = MAP2;
                    currentMapItems = MAP2_ITEMS;
                    currentLevel++;
                    currentLevelName = "Algebra";
                    player.setMovementBoost(1.0f);
                    break;
                case (2):
                    currentMap = MAP3;
                    currentMapItems = MAP3_ITEMS;
                    break;
                }
                player.setPosition(138, 136);
            }

            // item picked



            player.move();
            view.setCenter(player.getPosition());
            window.setView(view);
            gui.setPosition(view);

            window.clear(sf::Color::Black);
            map.draw(window, currentMap, currentMapItems);
            player.draw(window);
            gui.update(coins, currentLevelName);
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
