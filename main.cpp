#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Global.h"
#include "GUI.h"
#include "Menu.h"
#include <iostream>


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
    Player player(PLAYER_MOVEMENT_SPEED);
    sf::View view = window.getDefaultView();

    // Map

    std::vector<std::vector<int>> currentMap;
    std::vector<std::vector<int>> currentMapItems;
    Map map(GRID_SIZE);
    int currentLevel = 1;
    currentMap = MAP1;
    currentMapItems = MAP1_ITEMS;

    // UI
    sf::Font font;
    if (!font.loadFromFile("fonts/font.ttf")) {
        std::cerr << "Nie uda�o si� za�adowa� czcionki!" << std::endl;
        return -1;
    }
    sf::Text coinText;
    GUI gui(font);
    int coins = 0;
    gui.update(coins, currentLevel);
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
                }
            }

            // Change lvl

            if (player.getPosition().x > 1300 && player.getPosition().y > 950) {
                
                switch (currentLevel) {
                case (1):
                    currentMap = MAP2;
                    currentMapItems = MAP2_ITEMS;
                    currentLevel++;
                    break;
                case (2):
                    currentMap = MAP3;
                    currentMapItems = MAP3_ITEMS;
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
            gui.update(coins, currentLevel);
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
