#ifndef END_MENU_H
#define END_MENU_H

#include "State.h"
#include <SFML/Graphics.hpp>

class End_Menu : public State
{
public:
    End_Menu(sf::RenderWindow*, int const obtained_score);

    void   handle() override;
    State* update() override;
    void   render() override;

private:
    void open_menu() override;

    int      score;
    sf::Text score_text{};
    sf::Text text{};
    sf::Font highscore_font{};
};

#endif
