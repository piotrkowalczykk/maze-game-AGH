#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Menu {
public:
    Menu();
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event& event, bool& startGame);

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture startButtonTexture1;
    sf::Texture startButtonTexture2;
    sf::Sprite buttonSprite;
    bool buttonHovered;
};

#endif
