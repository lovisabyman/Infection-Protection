#include "New_Highscore.h"
#include "State.h"
#include "End_Menu.h"
#include "Game.h"
#include "Button.h"
#include "Resource_Manager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

using namespace sf;


New_Highscore::New_Highscore(RenderWindow* incoming_window_ptr, const int score)
                             : State(incoming_window_ptr), score{score}
{
    inputs["close"] = false;
    inputs["ok"] = false;

    open_menu();

    font = Resource_Manager::load_font(Read_From_File::nh_font);

    Vector2f background_size{Read_From_File::nh_text_background_size_x,
                             Read_From_File::nh_text_background_size_y};
    text_background.setPosition(window_ptr->getSize().x/2 -
                                background_size.x/2, window_ptr->getSize().y/2 -
                                background_size.y/2);
    text_background.setSize(background_size);
    text_background.setFillColor(Color::Black);

    player_name_text.setFont(font);
    player_name_text.setCharacterSize(background_size.x *
                                      Read_From_File::nh_char_relative_size);
    player_name_text.setPosition(text_background.getPosition());
    player_name_text.setFillColor(Color::White);

    Vector2f message_pos{Read_From_File::nh_message_pos_x,
                         Read_From_File::nh_message_pos_y};
    message_text.setFont(font);
    message_text.setCharacterSize(Read_From_File::nh_message_char_size);
    message_text.setPosition(message_pos);
    message_text.setFillColor(Color::Black);
    message_text.setString("Enter name:");

    Vector2f warning_pos{window_ptr->getSize().x/2 - background_size.x/2,
                         Read_From_File::nh_warning_pos_y};
    warning_text.setFont(font);
    warning_text.setCharacterSize(Read_From_File::nh_warning_char_size);
    warning_text.setPosition(warning_pos);
    warning_text.setFillColor(Color::Red);

    Vector2f highscore_pos{Read_From_File::nh_highscore_pos_x,
                           Read_From_File::nh_highscore_pos_y};
    highscore_text.setFont(font);
    highscore_text.setCharacterSize(Read_From_File::nh_highscore_char_size);
    highscore_text.setPosition(highscore_pos);
    highscore_text.setFillColor(Color::Red);
    highscore_text.setString("You got highscore!");

}


void New_Highscore::handle()
{
  Event event;
  while (window_ptr->pollEvent(event))
  {
      if (event.type == Event::Closed)
      {
          inputs["close"] = true;
      }

      else if ( event.type == Event::MouseButtonPressed )
      {
          auto mouse { event.mouseButton };
          if ( mouse.button == Mouse::Button::Left )
          {
              for (auto it = begin(buttons); it != end(buttons); ++it)
              {
                  inputs[it->get_name()] = it->is_pressed(mouse.x, mouse.y);
              }
          }
      }
      else if (event.type == Event::TextEntered)
      {
          if (event.text.unicode == 13)
          {
              if(player_name.length() >= 1)
              {
                  inputs["ok"] = true;
              }
              else
              {
                  warning_text.setString("Enter at least one character");
              }
          }
          else if (event.text.unicode == 8)
          {
              player_name = player_name.substr(0, player_name.length() - 1);
          }
          //Ta bara med vanliga bokstäver
          else if (event.text.unicode <= 126 && event.text.unicode >= 33)
          {
              if(static_cast<int>(player_name.length()) ==
                 Read_From_File::nh_nr_char_in_name)
              {
                  player_name[Read_From_File::nh_nr_char_in_name -1] =
                  static_cast<char>(event.text.unicode);
              }
              else
              {
                  player_name += static_cast<char>(event.text.unicode);
              }
          }
      }
  }
}


State* New_Highscore::update()
{
    if (caret_timer-- == 0)
    {
        caret_timer = Read_From_File::nh_caret_blink_timer;
    }
    if (caret_timer <= Read_From_File::nh_caret_blink_timer / 2 &&
        player_name.back() != '|' &&
        static_cast<int>(player_name.length()) !=
        Read_From_File::nh_nr_char_in_name)
    {
        player_name += '|';
    }
    else if(caret_timer >= Read_From_File::nh_caret_blink_timer / 2 &&
            player_name.back() == '|')
    {
        player_name = player_name.substr(0, player_name.length() - 1);
    }

    player_name_text.setString(player_name);

    if(player_name.back() == '|')
    {
        player_name = player_name.substr(0, player_name.length() - 1);
    }
    State* next_state{this};
    for (auto it = begin(inputs); it != end(inputs); ++it)
    {
        if(it->second)
        {
            if (it->first == "ok")
            {
                if (player_name.length() >= 1)
                {
                    Resource_Manager::save_highscore(player_name, score);
                    next_state = new End_Menu(window_ptr, score);
                }
                else
                {
                    warning_text.setString("Enter at least one character");
                }
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


void New_Highscore::render()
{
    window_ptr->clear();
    for (auto it = begin(sprites); it != end(sprites); ++it)
    {
        window_ptr->draw(*it);
    }
    window_ptr->draw(message_text);
    window_ptr->draw(highscore_text);
    window_ptr->draw(text_background);
    window_ptr->draw(player_name_text);
    window_ptr->draw(warning_text);

    window_ptr->display();
}


void New_Highscore::open_menu()
{
    std::stringstream infile{Resource_Manager::
                             load_string("Data/New_Highscore.txt")};
    std::string section;
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
