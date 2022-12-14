#include "Highscore_Menu.h"
#include "State.h"
#include "Start_Menu.h"
#include "Resource_Manager.h"
#include "Read_From_File.h"
#include "Button.h"
#include "Object.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

using namespace sf;

Highscore_Menu::Highscore_Menu(RenderWindow* incoming_window_ptr) :
                               State(incoming_window_ptr)
{
    inputs["close"]  = false;
    inputs["return"] = false;

    open_menu();

    std::ifstream infile{"Data/Highscore_List.txt"};
    std::string file_contents{std::istreambuf_iterator<char>(infile),
                            std::istreambuf_iterator<char>()};

   font = Resource_Manager::load_font(Read_From_File::hi_font);

    text.setString       (file_contents);
    text.setFont         (font);
    text.setCharacterSize(Read_From_File::hi_character_size);
    text.setStyle        (sf::Text::Bold);
    text.setFillColor    (sf::Color::Black);
    text.setPosition     (Read_From_File::hi_text_pos_x,
                          Read_From_File::hi_text_pos_y);
}


void Highscore_Menu::handle()
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


State* Highscore_Menu::update()
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


void Highscore_Menu::render()
{
    window_ptr->clear();
    for (auto it = begin(sprites); it != end(sprites); ++it)
    {
        window_ptr->draw(*it);
    }
    window_ptr->draw(text);
    window_ptr->display();
}


void Highscore_Menu::open_menu()
{
    std::stringstream infile{Resource_Manager::
                             load_string("Data/Highscore_Menu.txt")};
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

        //F??r att g??ra knappar
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
}
