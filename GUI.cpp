#include "GUI.h"

GUI::GUI(sf::Font& font) {
    coinText.setFont(font);
    coinText.setCharacterSize(30);
    coinText.setFillColor(sf::Color::Yellow);
    coinText.setPosition(0, 10);
    coinText.setStyle(sf::Text::Bold);
    coinText.setOutlineColor(sf::Color::Black);
    coinText.setOutlineThickness(3);

    levelText.setFont(font);
    levelText.setCharacterSize(30);
    levelText.setFillColor(sf::Color::Cyan);
    levelText.setPosition(10, 10);
    levelText.setOutlineColor(sf::Color::Black);
    levelText.setOutlineThickness(3);
}

void GUI::update(int coins, std::string level) {
    levelText.setString("Level: " + level);
    coinText.setString("Coins: " + std::to_string(coins));
}

void GUI::draw(sf::RenderWindow& window) {
    window.draw(levelText);
    window.draw(coinText);
}

void GUI::setPosition(const sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    coinText.setPosition(viewCenter.x - viewSize.x / 2 + 10, viewCenter.y - viewSize.y / 2 + 50);
    levelText.setPosition(viewCenter.x - viewSize.x / 2 + 10, viewCenter.y - viewSize.y / 2 + 10);
}