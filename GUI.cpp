#include "GUI.h"

GUI::GUI(sf::Font& font) {
    coinText.setFont(font);
    coinText.setCharacterSize(30);
    coinText.setFillColor(sf::Color::Yellow);
    coinText.setPosition(10, 10);

    levelText.setFont(font);
    levelText.setCharacterSize(30);
    levelText.setFillColor(sf::Color::Cyan);
    levelText.setPosition(10, 50);
}

void GUI::update(int coins, int level) {
    coinText.setString("Coins: " + std::to_string(coins));
    levelText.setString("Level: " + std::to_string(level));
}

void GUI::draw(sf::RenderWindow& window) {
    window.draw(coinText);
    window.draw(levelText);
}

void GUI::setPosition(const sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    coinText.setPosition(viewCenter.x - viewSize.x / 2 + 10, viewCenter.y - viewSize.y / 2 + 10);
    levelText.setPosition(viewCenter.x - viewSize.x / 2 + 10, viewCenter.y - viewSize.y / 2 + 50);
}