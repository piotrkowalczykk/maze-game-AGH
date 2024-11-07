#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <string>

class GUI {
public:
    GUI(sf::Font& font);

    void update(int points, std::string level);
    void draw(sf::RenderWindow& window);
    void setPosition(const sf::View& view);


private:
    sf::Text pointText;
    sf::Text levelText;
};

#endif // GUI_H
