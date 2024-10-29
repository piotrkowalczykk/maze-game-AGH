#include <SFML\Graphics.hpp>
#include "Player.h"

int main() {

	sf::RenderWindow window(sf::VideoMode(512,512), "Engineer path", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(512.0f, 512.0f));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("player.png");

	Player player(&playerTexture, sf::Vector2u(6, 5), 0.3f, 100.0f);

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
		view.setCenter(player.GetPosition());
		window.clear();
		window.setView(view);
		player.Draw(window);
		window.display();
	}
	return 0;
}