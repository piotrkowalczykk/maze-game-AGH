#include "Player.h"

Player::Player(float movementSpeed) : movementSpeed(movementSpeed) {
    texture.loadFromFile("textures/player1.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    sprite.setPosition(140, 136);
    float scale = 50.0f / 64.0f;
    sprite.setScale(scale, scale);
}

void Player::handleInput(float dt) {
    velocity = { 0.0f, 0.0f };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        updateTextureRect(150);
        velocity.y = -movementSpeed * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        updateTextureRect(0);
        velocity.y = movementSpeed * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        updateTextureRect(50);
        velocity.x = -movementSpeed * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        updateTextureRect(100);
        velocity.x = movementSpeed * dt;
    }
}

void Player::move() {
    sprite.move(velocity);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::resolveCollision(const sf::FloatRect& wallBounds) {
    sf::FloatRect playerBounds = getBounds();
    sf::FloatRect nextPos = playerBounds;
    nextPos.left += velocity.x;
    nextPos.top += velocity.y;

    if (wallBounds.intersects(nextPos)) {
        if (playerBounds.top < wallBounds.top && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
            && playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.left + playerBounds.width > wallBounds.left) {
            velocity.y = 0.0f;
            setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
        }
        else if (playerBounds.top > wallBounds.top && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
            && playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.left + playerBounds.width > wallBounds.left) {
            velocity.y = 0.0f;
            setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
        }
        if (playerBounds.left < wallBounds.left && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
            && playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top) {
            velocity.x = 0.0f;
            setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
        }
        else if (playerBounds.left > wallBounds.left && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
            && playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top) {
            velocity.x = 0.0f;
            setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
        }
    }
}

bool Player::checkItemCollision(const sf::FloatRect& coinBounds) {
    sf::FloatRect playerBounds = getBounds();
    if (playerBounds.intersects(coinBounds))
        return true;
    return false;
}

void Player::updateTextureRect(int offsetY) {
    int frame = static_cast<int>((sprite.getPosition().x + sprite.getPosition().y) / 25) % 4;
    int xTexture = frame * 50;
    sprite.setTextureRect(sf::IntRect(xTexture, offsetY, 50, 50));
}
