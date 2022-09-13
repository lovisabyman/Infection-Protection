#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
    Button(std::string, sf::Vector2u, sf::Vector2f);
    Button(Button const&) = default;
    Button(Button&&) = delete;
    Button& operator=(Button const&) = delete;
    Button& operator=(Button&&) = delete;
    ~Button() = default;

    bool is_pressed(int, int);
    std::string get_name() {return name;}

private:
    std::string name;
    sf::Vector2u size;
    sf::Vector2f position;
};

#endif
