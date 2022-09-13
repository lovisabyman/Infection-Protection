#include "Help_Menu.h"
#include "Start_Menu.h"
#include "State.h"
#include "Button.h"
#include "Resource_Manager.h"
#include "Read_From_File.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace sf;


Help_Menu::Help_Menu(RenderWindow* incoming_window_ptr) :
                     State(incoming_window_ptr)
{
    inputs["close"]  = false;
    inputs["return"] = false;

    open_menu();
}


void Help_Menu::handle()
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


State* Help_Menu::update()
{
    State* next_state{this};
    for (auto it = begin(inputs); it != end(inputs); ++it)
    {
        if(it->second)
        {
            if      (it->first == "return")
            {
                next_state = new Start_Menu(window_ptr);
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


void Help_Menu::render()
{
    window_ptr->clear();
    for (auto it = begin(sprites); it != end(sprites); ++it)
    {
        window_ptr->draw(*it);
    }
    for (auto it = begin(texts); it != end(texts); ++it)
    {
        window_ptr->draw(*it);
    }
    window_ptr->display();
}


void Help_Menu::open_menu()
{
    std::stringstream infile{Resource_Manager::
                             load_string("Data/Help_Menu.txt")};
    std::string section{};
    while (infile >> section)
    {
        if(section == "EOI")
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

        Texture& texture{Resource_Manager::load_graphics(filename)};
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
                             (size_y * window_ptr->getSize().y)};
        Vector2f button_pos{sprite.getPosition().x -
                            size_x * window_ptr->getSize().x / 2,
                            sprite.getPosition().y -
                            size_y * window_ptr->getSize().y / 2};
        Button button{name, button_size, button_pos};
        buttons.push_back(button);
    }
    font = Resource_Manager::load_font(Read_From_File::hem_font);

    while (infile >> section)
    {
        if(section == "EOT")
        {
            break;
        }
        std::string string_text{};
        int character_size{};
        float pos_x;
        float pos_y;
        Text text{};
        infile >> string_text;
        infile >> character_size;
        infile >> pos_x;
        infile >> pos_y;

        std::replace(string_text.begin(), string_text.end(), '_', ' ');

        text.setFont         (font);
        text.setString       (string_text);
        text.setCharacterSize(character_size);
        text.setPosition     (pos_x * window_ptr->getSize().x,
                              pos_y * window_ptr->getSize().y);
        text.setFillColor    (sf::Color::Black);
        texts.push_back      (text);
    }
}
