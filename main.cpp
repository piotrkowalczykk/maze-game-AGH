#include <SFML\Graphics.hpp>
#include <vector>
#include "Character.h"
#include "Player.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Enginner path");
	std::vector<Character*> characters;
	characters.push_back(new Player());

	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float deltaTime = clock.restart().asSeconds();

		for (Character* character : characters)
			character->Update(deltaTime);

		window.clear(sf::Color(135, 206, 235)); // ustawienie koloru tla
		
		for (Character* character : characters)
			character->Draw(window);

		window.display();
	}
	return 0;
}