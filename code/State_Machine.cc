#include "State.h"
#include "Start_Menu.h"
#include "Game.h"
#include "Read_From_File.h"
#include "Resource_Manager.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    Read_From_File rff{};
    unsigned int const width {static_cast<unsigned int>
                             (Read_From_File::window_width)};
    unsigned int const height{static_cast<unsigned int>
                             (Read_From_File::window_height)};
    std::string game_name{Read_From_File::game_name};
    std::replace(game_name.begin(), game_name.end(), '_', ' ');
    RenderWindow window(VideoMode {width, height}, game_name,
                        Style::Titlebar | Style::Close);
    RenderWindow* window_ptr{&window};
    State *state = new Start_Menu(window_ptr);
    State *next_state{state};

    window.setFramerateLimit(Read_From_File::framerate);

    while(next_state != 0)
    {
        state->handle();
        next_state = state->update();
        state->render();
        if (next_state != state)
        {
            delete state;
            state = next_state;
        }
    }

    window.close();

    return 0;
}
