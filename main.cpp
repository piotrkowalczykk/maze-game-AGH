#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Global.h"
#include "Menu.h"
#include <iostream>

int main() {
    // Game
    sf::Clock dt_clock;
    float deltaTime;

    // Window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);
    window.setFramerateLimit(FRAMERATE_LIMIT);

    // Main Menu
    Menu menu;
    bool startGame = false;

    // Player
    Player player(PLAYER_MOVEMENT_SPEED);
    sf::View view = window.getDefaultView();

    // Map
    std::vector<std::vector<int>> currentMap;
    Map map(GRID_SIZE);
    currentMap = MAP2;

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
                    if (currentMap[y][x] == 1) {
                        sf::FloatRect wallBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                        player.resolveCollision(wallBounds);
                    }
                }
            }

            std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;
            if (player.getPosition().x > 1300 && player.getPosition().y > 950) {
                currentMap = MAP1;
                player.setPosition(138, 136);
            }

            player.move();
            view.setCenter(player.getPosition());
            window.setView(view);

            window.clear(sf::Color::Black);
            map.draw(window, currentMap);
            player.draw(window);
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
