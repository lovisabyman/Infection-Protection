#include "State.h"
#include "Game.h"
#include "New_Highscore.h"
#include "End_Menu.h"
#include "Resource_Manager.h"
#include "Read_From_File.h"
#include "Object.h"
#include "Wall.h"
#include "Player.h"
#include "Default_Player.h"
#include "RoF_Powerup.h"
#include "Shielded_Powerup.h"
#include "Big_Ball.h"
#include "Small_Ball.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <list>

using namespace sf;


Game::Game(RenderWindow* incoming_window_ptr) : State(incoming_window_ptr)
{
    inputs["close"]       = false;
    inputs["Right_arrow"] = false;
    inputs["Left_arrow"]  = false;
    inputs["Up_arrow"]    = false;

    open_menu();
    float window_size_x{static_cast<float>(window_ptr->getSize().x)};
    float window_size_y{static_cast<float>(window_ptr->getSize().y)};
    float wall_width{window_size_x*Read_From_File::wall_width_factor};
    Position left_wall{0, window_size_y, 0, wall_width, wall_width,
                       window_size_y};
    Position right_wall{0, window_size_y, window_size_x - wall_width,
                        window_size_x, wall_width, window_size_y};
    Position player{window_size_y - Read_From_File::player_height,
                    window_size_y,
                    window_size_x / 2 - Read_From_File::player_width / 2,
                    window_size_x / 2 + Read_From_File::player_width / 2,
                    Read_From_File::player_width,
                    Read_From_File::player_height};
    objects.push_back(new Default_Player(player));
    objects.push_back(new Wall(left_wall));
    objects.push_back(new Wall(right_wall));

    srand(time(NULL));

    StartRec.setSize(Vector2f(Read_From_File::g_score_rect_initial_size_x,
                              Read_From_File::g_score_rect_size_y));
    StartRec.setPosition(Read_From_File::g_score_rect_pos_x,
                         Read_From_File::g_score_rect_pos_y);
    StartRec.setFillColor(Color::Red);
    StartRec.setOutlineColor(Color::Black);
    StartRec.setOutlineThickness(Read_From_File::
                                 g_score_rect_outline_thickness);

    font = Resource_Manager::load_font(Read_From_File::g_font);
    score_text.setFont(font);
    score_text.setCharacterSize(Read_From_File::g_score_character_size);
    score_text.setStyle(Text::Bold);
    score_text.setFillColor(Color::Black);
}


Game::~Game()
{
    for (unsigned int i{0}; i<objects.size(); i++)
    {
        delete objects[i];
    }
}


void Game::handle()
{
    Event event;
    while (window_ptr->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            inputs["close"] = true;
        }
    }
    if(Keyboard::isKeyPressed(Read_From_File::move_right))
    {
        inputs["Right_arrow"] = true;
    }
    if(Keyboard::isKeyPressed(Read_From_File::move_left))
    {
        inputs["Left_arrow"] = true;
    }
    if(Keyboard::isKeyPressed(Read_From_File::shoot))
    {
        inputs["Up_arrow"] = true;
    }
}


State* Game::update()
{
    update_score();
    create_powerups();
    create_enemies();

    //Uppdaterar objekten
    for (unsigned int i{0}; i<objects.size(); i++)
    {
        objects[i]->update(inputs, objects);
    }

    State* next_state{this};
    handle_collision(next_state);

    if(inputs["close"])
    {
        next_state      = nullptr;
        inputs["close"] = false;
    }

    return next_state;
}


//Koden i collide är delvis hämtad från föreläsning 8 av kursen TDDC76
//https://www.ida.liu.se/~TDDC76/2020/fo/slides/project/project.pdf
bool Game::collide(Object* const& object1, Object* const& object2) const
{
    Position object1_pos{object1->get_position()};
    Position object2_pos{object2->get_position()};
    return !(object1_pos.left   > object2_pos.right ||
             object1_pos.top    > object2_pos.bottom||
             object1_pos.right  < object2_pos.left  ||
             object1_pos.bottom < object2_pos.top);
}


void Game::create_enemies()
{
    if(--enemy_pattern_timer == 0)
    {
        create_pattern();
        enemy_pattern_timer  = Read_From_File::enemy_pattern_interval;
        enemy_spawn_interval = Read_From_File::enemy_pattern_interval
                               / enemy_pattern.size();
        enemy_spawn_timer    = enemy_spawn_interval;
        spawn_enemies();
    }
    else if (--enemy_spawn_timer == 0 && enemy_pattern.size() != 0)
    {
        spawn_enemies();
        enemy_spawn_timer = enemy_spawn_interval;
    }
}


void Game::create_pattern()
{
    int curr_weight{enemy_weight};
    while (curr_weight)
    {
        int biggest_size;
        //Största storleken en boll kan ha.
        biggest_size = floor(log2(curr_weight + 1));
        //Få ett tal mellan 1 och biggest_size.
        int size{rand() % biggest_size + 1};
        enemy_pattern.push_back(size);
        curr_weight -= pow(2,size) - 1;
    }
    //Ser till att största bollen kommer sist i mönstret.
    auto biggest_ball = std::max_element(enemy_pattern.begin(),
                                         enemy_pattern.end());
    auto end_ball = enemy_pattern.end();
    end_ball--;
    std::swap((*end_ball), (*biggest_ball));

    enemy_weight += Read_From_File::enemy_increase_weight;
}


void Game::spawn_enemies()
{
    //Åker åt vänster om true.
    bool spawn_direction{rand() % 2};
    int enemy_size{};
    if (enemy_pattern.front() == 1)
    {
        enemy_size = ball_texture.getSize().x * Read_From_File::size_small_ball;
    }
    else
    {
        enemy_size = 1 + ball_texture.getSize().x
                     * Read_From_File::origin_size_ball
                     * pow(Read_From_File::ball_encrease_size,
                           enemy_pattern.front() - 1
                           - Read_From_File::decreas_divide);
    }
    int x_pos{};
    x_pos = rand() % static_cast<int>(window_ptr->getSize().x - 2 *
              spawn_margin - enemy_size) + spawn_margin;
    if(enemy_pattern.front() == 1)
    {
        objects.push_back(new Small_Ball(x_pos, spawn_direction));
    }
    else
    {
        objects.push_back(new Big_Ball(enemy_pattern.front()-1, x_pos,
                                       spawn_direction));
    }
    enemy_pattern.pop_front();
}


void Game::create_powerups()
{
    int powerup_size{std::max(static_cast<int>
                             (Read_From_File::shield_powerup_width),
                             static_cast<int>
                             (Read_From_File::rof_powerup_width))};
    int x_pos{rand() % static_cast<int>(window_ptr->getSize().x
                                        - 2 * spawn_margin - powerup_size)
                                        + spawn_margin};
    powerup_timer++;
    if (powerup_timer * powerup_weight > Read_From_File::powerup_limit)
    {
        if (powerup_type == 1)
        {
            objects.push_back(new Shielded_powerup(x_pos));
            powerup_type = rand() % 2;
        }
        else
        {
            objects.push_back(new RoF_powerup(x_pos));
            powerup_type = rand() % 2;
        }
        powerup_timer = 0;
        powerup_weight = rand() % (Read_From_File::powerup_weight_max
                                   + Read_From_File::powerup_weight_min) / 2
                                + (Read_From_File::powerup_weight_max
                                   - Read_From_File::powerup_weight_min) / 2;
    }
}


void Game::update_score()
{
    if (score_timer-- <= 0)
    {
        score++;

        if(score >= Read_From_File::score_board_second_size_l &&
          score < Read_From_File::score_board_second_size_u )
        {
            StartRec.setSize(Vector2f
                            (Read_From_File::g_score_rect_2digit_size_x,
                             Read_From_File::g_score_rect_size_y));
        }
        if(score >= Read_From_File::score_board_third_size_l &&
          score < Read_From_File::score_board_third_size_u )
        {
            StartRec.setSize(Vector2f
                            (Read_From_File::g_score_rect_3digit_size_x,
                             Read_From_File::g_score_rect_size_y));
        }
        if(score >= Read_From_File::score_board_fourth_size_l &&
          score < Read_From_File::score_board_fourth_size_u)
        {
            StartRec.setSize(Vector2f
                            (Read_From_File::g_score_rect_4digit_size_x,
                             Read_From_File::g_score_rect_size_y));
        }
        else if(score >= Read_From_File::score_board_max_size)
        {
            StartRec.setSize(Vector2f
                            (Read_From_File::g_score_rect_5digit_size_x,
                             Read_From_File::g_score_rect_size_y));
        }
        score_timer = Read_From_File::framerate / Read_From_File::score_per_sec;
        std::string printstring = " " + Read_From_File::score_board
                                  + std::to_string(score);
        score_text.setString(printstring);
    }
}


int Game::get_lowest_highscore()
{
    std::ifstream highscore;
    int curr_pos{};
    std::string curr_name{};
    int curr_score{};
    highscore.open("Data/Highscore_List.txt");
    while(highscore >> curr_pos)
    {
        highscore >> curr_name;
        highscore >> curr_score;
    }
    return curr_score;
}

void Game::handle_collision(State* & next_state)
{
    long unsigned int vec_size{objects.size()};
    for (unsigned int i{0}; i<vec_size; i++)
    {
        for (unsigned int j{i + 1}; j<vec_size; j++)
        {
            if(objects[i] != objects[j] && collide(objects[i], objects[j]))
            {
                //Kör objektens kollissionshantering
                bool destroy1{false};
                bool destroy2{false};
                destroy1 = objects[i]->handle_collision(objects[j], objects);
                destroy2 = objects[j]->handle_collision(objects[i], objects);
                //Kollar om spelaren har tagits bort, i sånt fall avslutas
                //spelet.
                if((destroy1 && dynamic_cast<Player*>(objects[i]) != nullptr) ||
                   (destroy2 && dynamic_cast<Player*>(objects[j]) != nullptr))
                {
                    int lowest_highscore{get_lowest_highscore()};
                    if (lowest_highscore < score)
                    {
                        next_state = new New_Highscore(window_ptr, score);
                    }
                    else
                    {
                        next_state = new End_Menu(window_ptr, score);
                    }
                }
                //Förstör object som ska förstöras.
                if(destroy1 && destroy2)
                {
                    auto it1 = std::find(objects.begin(), objects.end(),
                                         objects[i]);
                    delete (*it1);
                    objects.erase(it1);
                    auto it2 = std::find(objects.begin(), objects.end(),
                                         objects[j-1]);
                    delete (*it2);
                    objects.erase(it2);
                }
                else if(destroy1)
                {
                    auto it1 = std::find(objects.begin(), objects.end(),
                                         objects[i]);
                    delete (*it1);
                    objects.erase(it1);
                }
                else if(destroy2)
                {
                    auto it2 = std::find(objects.begin(), objects.end(),
                                         objects[j]);
                    delete (*it2);
                    objects.erase(it2);
                }
            }
        }
    }
}

void Game::render()
{
    window_ptr->clear();
    for (auto it = begin(sprites); it != end(sprites); ++it)
    {
        window_ptr->draw(*it);
    }
    for (unsigned int i{0}; i<objects.size(); i++)
    {
        objects[i]->render(window_ptr);
    }
    window_ptr->draw(StartRec);
    window_ptr->draw(score_text);

    window_ptr->display();
}


void Game::open_menu()
{
    std::stringstream infile{Resource_Manager::load_string("Data/Game.txt")};
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
    }
}
