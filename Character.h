#pragma once

#include <SFML\Graphics.hpp>
class Character
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
protected:
	sf::FloatRect rect;
};

