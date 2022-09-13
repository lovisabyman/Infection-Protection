#ifndef START_MENU_H
#define START_MENU_H

#include "State.h"
#include <SFML/Graphics.hpp>

class Start_Menu : public State
{
public:
    Start_Menu(sf::RenderWindow*);

    void   handle() override;
    State* update() override;
    void   render() override;

private:
    void open_menu() override;
};

#endif
