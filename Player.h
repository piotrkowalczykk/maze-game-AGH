#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player();
	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window) override;
private:
	float speed;
	float verticalVelocity;
	float gravity;
	bool isFacingLeft;
	sf::Texture texture;
	sf::Sprite sprite;
};

