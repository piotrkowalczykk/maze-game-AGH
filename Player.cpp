#include "Player.h"
#include <iostream>
#include "Global.h"

Player::Player() : speed(300), verticalVelocity(0), gravity(1000), isFacingLeft(false)
{
	rect = sf::FloatRect(50, 50, 100, 100);
	texture.loadFromFile("textures/player.png");
	sprite = sf::Sprite(texture);
}

void Player::Update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rect.left -= speed * deltaTime;
		isFacingLeft = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rect.left += speed * deltaTime;
		isFacingLeft = false;
	}


	rect.top += verticalVelocity * deltaTime;
	verticalVelocity += gravity * deltaTime;

	if ((rect.top + rect.height) > HEIGHT)
		rect.top = HEIGHT - rect.height;

	sprite.setPosition(rect.left, rect.top);
	sprite.setScale(rect.width / texture.getSize().x, rect.height / texture.getSize().y);
	sprite.setTextureRect(sf::IntRect(texture.getSize().x * (isFacingLeft ? 1 : 0), 0, texture.getSize().x * (isFacingLeft ? -1 : 1), texture.getSize().y));
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
