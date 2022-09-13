#include "Start_Menu.h"
#include "State.h"
#include "Highscore_Menu.h"
#include "Help_Menu.h"
#include "Game.h"
#include "Button.h"
#include "Resource_Manager.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

using namespace sf;


Start_Menu::Start_Menu(RenderWindow* incoming_window_ptr) :
                       State(incoming_window_ptr)
{
    inputs["close"]     = false;
    inputs["play"]      = false;
    inputs["highscore"] = false;

    open_menu();
}


void Start_Menu::handle()
{
    Event event;
    while (window_ptr->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            inputs["close"] = true;
        }
        else if (event.type == Event::MouseButtonPressed)
        {
            auto mouse {event.mouseButton};
            if (mouse.button == Mouse::Button::Left)
            {
                for (auto it = begin(buttons); it != end(buttons); ++it)
                {
                    inputs[it->get_name()] = it->is_pressed(mouse.x, mouse.y);
                }
            }
        }
    }
}


State* Start_Menu::update()
{
    State* next_state{this};
    for (auto it = begin(inputs); it != end(inputs); ++it)
    {
        if(it->second)
        {
            if      (it->first == "play")
            {
                next_state = new Game(window_ptr);
            }
            else if (it->first == "highscore")
            {
                next_state = new Highscore_Menu(window_ptr);
            }
            else if (it->first == "help")
            {
                next_state = new Help_Menu(window_ptr);
            }
            else if (it->first == "close")
            {
                next_state = nullptr;
            }
            it->second = false;
        }
    }
    return next_state;
}


void Start_Menu::render()
{
    window_ptr->clear();
    for (auto it = begin(sprites); it != end(sprites); ++it)
    {
        window_ptr->draw(*it);
    }
    window_ptr->display();
}


void Start_Menu::open_menu()
{
    std::stringstream infile{Resource_Manager::
                             load_string("Data/Start_Menu.txt")};
    std::string section{};
    while (infile >> section)
    {
        if(section == "EOF")
        {
            break;
        }
        std::string name{};
        std::string filename{};
        float size_x;
        float size_y;
        float pos_x;
        float pos_y;
        infile >> name;
        infile >> filename;
        infile >> size_x;
        infile >> size_y;
        infile >> pos_x;
        infile >> pos_y;

        Texture& texture {Resource_Manager::load_graphics(filename)};
        textures[name] = texture;
        Sprite sprite{textures[name]};
        Vector2f size{size_x * window_ptr->getSize().x / texture.getSize().x,
                      size_y * window_ptr->getSize().y / texture.getSize().y};
        Vector2f pos{pos_x * window_ptr->getSize().x,
                     pos_y * window_ptr->getSize().y};

        sprite.setOrigin(Vector2f(texture.getSize().x / 2,
                                  texture.getSize().y / 2));
        sprite.setScale(size);
        sprite.setPosition(pos);
        sprites.push_back(sprite);

        //För att göra knappar
        Vector2u button_size{static_cast<unsigned int>
                             (size_x * window_ptr->getSize().x),
                             static_cast<unsigned int>
                             (size_y *window_ptr->getSize().y)};
        Vector2f button_pos{sprite.getPosition().x -
                            size_x * window_ptr->getSize().x/2,
                            sprite.getPosition().y -
                            size_y * window_ptr->getSize().y/2};
        Button button{name, button_size, button_pos};
        buttons.push_back(button);
    }
}
