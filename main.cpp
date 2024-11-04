#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

using namespace sf;

void drawMap(RenderWindow& window, const std::vector<std::vector<int>>& map, float gridSize) {
	for (size_t y = 0; y < map.size(); ++y) {
		for (size_t x = 0; x < map[y].size(); ++x) {
			if (map[y][x] == 1) { // Jeœli wartoœæ to 1, rysuj œcianê
				RectangleShape wall(Vector2f(gridSize, gridSize));
				wall.setFillColor(Color::Red);
				wall.setPosition(x * gridSize, y * gridSize);
				window.draw(wall);
			}
		}
	}
}

int main() {

	const unsigned WINDOW_WIDTH = 800;
	const unsigned WINDOW_HEIGHT = 608;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Egineer path");
	window.setFramerateLimit(120);

	float dt;
	Clock dt_clock;

	const float gridSize = 64.0f;

	//Player

	const float movementSpeed = 200.0f;
	View view = window.getDefaultView();
	Vector2f velocity;
	Sprite player;
	Texture t1;
	t1.loadFromFile("textures/player1.png");
	player.setTexture(t1);
	player.setTextureRect(IntRect(0, 0, 64, 64));
	player.setPosition(64, 400);

	//Wals

	std::vector<std::vector<int>> map = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	// Collision

	FloatRect nextPos;

	while (window.isOpen())
	{
		dt = dt_clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Player movement

		velocity.y = 0.0f;
		velocity.x = 0.0f;

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			int xTexture = 0;
			xTexture = (int)player.getPosition().y / 25 % 4;
			xTexture = xTexture * 64;
			player.setTextureRect(IntRect(xTexture, 192, 64, 64));
			velocity.y += -movementSpeed * dt;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			int xTexture = 0;
			xTexture = (int)player.getPosition().y / 25 % 4;
			xTexture = xTexture * 64;
			player.setTextureRect(IntRect(xTexture, 0, 64, 64));
			velocity.y += movementSpeed * dt;
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			int xTexture = 0;
			xTexture = (int)player.getPosition().x / 25 % 4;
			xTexture = xTexture * 64;
			player.setTextureRect(IntRect(xTexture, 64, 64, 64));
			velocity.x += -movementSpeed * dt;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			int xTexture = 0;
			xTexture = (int)player.getPosition().x / 25 % 4;
			xTexture = xTexture * 64;
			player.setTextureRect(IntRect(xTexture, 128, 64, 64));
			velocity.x += movementSpeed * dt;
		}

		// Collision

		for (size_t y = 0; y < map.size(); ++y) {
			for (size_t x = 0; x < map[y].size(); ++x) {
				if (map[y][x] == 1) {
					FloatRect playerBounds = player.getGlobalBounds();
					FloatRect wallBounds(x * gridSize, y * gridSize, gridSize, gridSize);

					nextPos = playerBounds;
					nextPos.left += velocity.x;
					nextPos.top += velocity.y;

					if (wallBounds.intersects(nextPos)) {
						// Kolizja z do³u
						if (playerBounds.top < wallBounds.top
							&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left) {
							velocity.y = 0.0f;
							player.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
						}
						// Kolizja z góry
						else if (playerBounds.top > wallBounds.top
							&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left) {
							velocity.y = 0.0f;
							player.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
						}
						// Kolizja z prawej
						if (playerBounds.left < wallBounds.left
							&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height > wallBounds.top) {
							velocity.x = 0.0f;
							player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
						}
						// Kolizja z lewej
						else if (playerBounds.left > wallBounds.left
							&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height > wallBounds.top) {
							velocity.x = 0.0f;
							player.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
						}
					}
				}
			}
		}


		player.move(velocity);


		// Render

		view.setCenter(player.getPosition().x, player.getPosition().y);
		window.setView(view);
		window.clear(Color(0,255,0));
		drawMap(window, map, gridSize);
		window.draw(player);
		window.display();
	}

	return 0;
}