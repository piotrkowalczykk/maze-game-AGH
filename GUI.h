#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <string>

class GUI {
public:
    GUI(sf::Font& font);

    void update(int coins, int level);
    void draw(sf::RenderWindow& window);
    void setPosition(const sf::View& view);


private:
    sf::Text coinText;
    sf::Text levelText;
};

#endif // GUI_H
