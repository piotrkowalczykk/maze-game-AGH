#pragma once
#include <SFML\Graphics.hpp>
#include "Collision.h"
class Map
{
public:
	Map(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Map();

	void Draw(sf::RenderWindow& window);
	Collision GetCollision() { return Collision(body); }

private:
	sf::RectangleShape body;
};