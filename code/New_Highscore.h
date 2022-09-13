#ifndef NEW_HIGHSCORE_H
#define NEW_HIGHSCORE_H

#include "State.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Read_From_File.h"

class New_Highscore : public State
{
public:
    New_Highscore(sf::RenderWindow*, const int score);

    void handle();
    State* update();
    void render();

private:
    void open_menu() override;
    
    int score;
    std::string player_name{};
    sf::Text message_text{};
    sf::Text warning_text{};
    sf::Text highscore_text{};
    sf::Text player_name_text{};
    sf::RectangleShape text_background{};
    int caret_timer{Read_From_File::nh_caret_blink_timer};
};

#endif
