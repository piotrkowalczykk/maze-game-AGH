#include "GUI.h"

GUI::GUI(sf::Font& font) {
    pointText.setFont(font);
    pointText.setCharacterSize(30);
    pointText.setFillColor(sf::Color::Yellow);
    pointText.setPosition(0, 10);
    pointText.setStyle(sf::Text::Bold);
    pointText.setOutlineColor(sf::Color::Black);
    pointText.setOutlineThickness(3);

    levelText.setFont(font);
    levelText.setCharacterSize(30);
    levelText.setFillColor(sf::Color::Cyan);
    levelText.setPosition(10, 10);
    levelText.setOutlineColor(sf::Color::Black);
    levelText.setOutlineThickness(3);
}

void GUI::update(int points, std::string level) {
    levelText.setString(level);
    pointText.setString("Plusy: " + std::to_string(points));
}

void GUI::draw(sf::RenderWindow& window) {
    window.draw(levelText);
    window.draw(pointText);
}

void GUI::setPosition(const sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    pointText.setPosition(viewCenter.x - viewSize.x / 2 + 10, viewCenter.y - viewSize.y / 2 + 50);
    levelText.setPosition(viewCenter.x - viewSize.x / 2 + 10, viewCenter.y - viewSize.y / 2 + 10);
}