#include "GameOver.h"
#include <iostream>
#include <string>
#include "Global.h"
#include <SFML\Graphics.hpp>


GameOver::GameOver() {

    if (!font.loadFromFile("fonts/font.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Ustawienia tekstu "Koniec gry"
    gameOverText.setFont(font);
    gameOverText.setString("Koniec gry");
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(WINDOW_WIDTH / 2.0f - gameOverText.getGlobalBounds().width / 2.0f, 150);
    points = 0;

    // Ustawienia tekstu z wynikiem
    scoreText.setFont(font);
    scoreText.setString("Twoje plusy: " + std::to_string(points));
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(WINDOW_WIDTH / 2.0f - scoreText.getGlobalBounds().width / 2.0f, 250);

    // Ustawienia przycisku "Menu"
    menuButtonTexture1.loadFromFile("textures/menuBtn1.png");
    menuButtonTexture2.loadFromFile("textures/menuBtn2.png");
    menuButton.setTexture(menuButtonTexture1);
    menuButton.setPosition(160, 350);
}

void GameOver::draw(sf::RenderWindow& window) {
    window.draw(gameOverText);
    window.draw(scoreText);
    window.draw(menuButton);
}

void GameOver::handleInput(sf::Event& event, bool& endGame, bool& startGame) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        buttonHovered = menuButton.getGlobalBounds().contains(mousePos);
        if (buttonHovered) {
            menuButton.setTexture(menuButtonTexture2);
        }
        else {
            menuButton.setTexture(menuButtonTexture1);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (buttonHovered) {
            endGame = false;
            startGame = false;
        }
    }
}

void GameOver::setPoints(int points)
{
    this->points = points;
    scoreText.setString("Twoje punkty: " + std::to_string(points));
}
