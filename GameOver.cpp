#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Global.h"

class GameOver {
private:
    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Text menuButtonText;
    sf::RectangleShape menuButton;
    sf::Font font;

public:
    GameOver(int score) {
        // Za³adowanie czcionki
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

        // Ustawienia tekstu z wynikiem
        scoreText.setFont(font);
        scoreText.setString("Twoje punkty: " + std::to_string(score));
        scoreText.setCharacterSize(40);
        scoreText.setFillColor(sf::Color::Yellow);
        scoreText.setPosition(WINDOW_WIDTH / 2.0f - scoreText.getGlobalBounds().width / 2.0f, 250);

        // Ustawienia przycisku "Menu"
        menuButton.setSize(sf::Vector2f(200, 60));
        menuButton.setFillColor(sf::Color::Blue);
        menuButton.setPosition(WINDOW_WIDTH / 2.0f - menuButton.getSize().x / 2.0f, 400);

        menuButtonText.setFont(font);
        menuButtonText.setString("Menu");
        menuButtonText.setCharacterSize(30);
        menuButtonText.setFillColor(sf::Color::White);
        menuButtonText.setPosition(
            WINDOW_WIDTH / 2.0f - menuButtonText.getGlobalBounds().width / 2.0f,
            415 // Pozycja w œrodku przycisku
        );
    }

    // Funkcja rysuj¹ca ekran Game Over
    void draw(sf::RenderWindow& window) {
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(menuButton);
        window.draw(menuButtonText);
    }

    // Funkcja obs³ugi klikniêcia przycisku "Menu"
    bool handleInput(sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            if (menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                return true; // Klikniêto przycisk "Menu"
            }
        }
        return false;
    }
};
