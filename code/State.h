#ifndef STATE_H
#define STATE_H

#include "Button.h"
#include "Read_From_File.h"
#include "Resource_Manager.h"
#include <vector>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class State
{
public:
    State(sf::RenderWindow*);
    State(State const&)            = delete;
    State(State&&)                 = delete;
    State& operator=(State const&) = delete;
    State& operator=(State&&)      = delete;
    virtual ~State()               = default;

    virtual void   handle() = 0;
    virtual State* update() = 0;
    virtual void   render() = 0;

protected:
    std::map<std::string, bool>        inputs{};
    std::vector<sf::Sprite>            sprites{};
    std::map<std::string, sf::Texture> textures{};
    std::vector<Button>                buttons{};
    sf::RenderWindow*                  window_ptr;
    sf::Vector2u                       window_size;
    sf::Font                           font{Resource_Manager::load_font
                                            (Read_From_File::state_font)};

    virtual void open_menu() = 0;
};

#endif
