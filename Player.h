#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float movementSpeed);
    void handleInput(float dt);
    void move();
    sf::FloatRect getBounds() const;
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    void resolveCollision(const sf::FloatRect& wallBounds);

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity;
    float movementSpeed;
    void updateTextureRect(int offsetY);
};

#endif
