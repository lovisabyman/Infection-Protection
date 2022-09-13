#ifndef HELP_MENU_H
#define HELP_MENU_H

#include "State.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Help_Menu : public State
{
public:
    Help_Menu(sf::RenderWindow*);

    void   handle() override;
    State* update() override;
    void   render() override;

private:
    void open_menu() override;
    
    std::vector<sf::Text> texts{};
};

#endif
