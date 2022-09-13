#ifndef HIGHSCORE_MENU_H
#define HIGHSCORE_MENU_H

#include "State.h"
#include <SFML/Graphics.hpp>

class Highscore_Menu : public State
{
public:
    Highscore_Menu(sf::RenderWindow*);

    void   handle() override;
    State* update() override;
    void   render() override;

private:
    void open_menu() override;

    sf::Text text{};
};

#endif
