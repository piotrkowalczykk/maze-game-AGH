#include "Menu.h"
#include <iostream>

Menu::Menu() {
    // Load the background image
    if (!backgroundTexture.loadFromFile("textures/logo.png")) {
        std::cerr << "Error loading image" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    
    startButtonTexture1.loadFromFile("textures/btn1.png");
    startButtonTexture2.loadFromFile("textures/btn2.png");
    buttonSprite.setTexture(startButtonTexture1);
    buttonSprite.setPosition(360, 490); // Adjust based on your window size

    buttonHovered = false;
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(buttonSprite);
}

void Menu::handleInput(sf::Event& event, bool& startGame) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        buttonHovered = buttonSprite.getGlobalBounds().contains(mousePos);
        if (buttonHovered) {

            buttonSprite.setTexture(startButtonTexture2); // Change color on hover
        }
        else {
            buttonSprite.setTexture(startButtonTexture1);// Default color
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (buttonHovered) {
            startGame = true; // Set flag to start the game
        }
    }
}
