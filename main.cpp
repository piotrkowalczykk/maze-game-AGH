#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Global.h"

int main() {

    // Game

    sf::Clock dt_clock;
    float deltaTime;

    // Window

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);
    window.setFramerateLimit(FRAMERATE_LIMIT);

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
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.handleInput(deltaTime);
        for (size_t y = 0; y < currentMap.size(); ++y) {
            for (size_t x = 0; x < currentMap[y].size(); ++x) {
                if (currentMap[y][x] == 1) {
                    sf::FloatRect wallBounds(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                    player.resolveCollision(wallBounds);
                }
            }
        }

        player.move();
        view.setCenter(player.getPosition());
        window.setView(view);

        window.clear(sf::Color::Black);
        map.draw(window, currentMap);
        player.draw(window);
        window.display();
    }

    return 0;
}
