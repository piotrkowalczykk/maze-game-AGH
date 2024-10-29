#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include <vector>

int main() {

	sf::RenderWindow window(sf::VideoMode(512, 512), "Engineer path", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(512.0f, 512.0f));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("player.png");

	Player player(&playerTexture, sf::Vector2u(6, 5), 0.3f, 100.0f, 200.0f);

	std::vector<Map> maps;
	maps.push_back(Map(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
	maps.push_back(Map(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
	maps.push_back(Map(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
		}

		player.Update(deltaTime);

		sf::Vector2f direction;

		for (Map& map : maps) {
			if (map.GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f))
				player.OnCollision(direction);
		}

		view.setCenter(player.GetPosition());
		window.clear();
		window.setView(view);
		player.Draw(window);
		for (Map& map : maps)
			map.Draw(window);
		window.display();
	}
	return 0;
}