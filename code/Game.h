#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "Object.h"
#include "Read_From_File.h"
#include "Resource_Manager.h"
#include <stdlib.h>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>



class Game : public State
{
public:
    Game(sf::RenderWindow*);
    ~Game() override;

    void handle()   override;
    State* update() override;
    void render()   override;

private:
    std::vector<Object*> objects{};
    sf::Texture ball_texture{Resource_Manager::
                             load_graphics(Read_From_File::ball_file)};
    int enemy_weight{Read_From_File::enemy_initial_weight};
    std::list<int> enemy_pattern{};
    int enemy_pattern_timer{Read_From_File::enemy_initial_pattern_timer};
    int enemy_spawn_timer{Read_From_File::enemy_initial_spawn_timer};
    int enemy_spawn_interval{Read_From_File::enemy_pattern_interval};

    int powerup_timer{};
    int powerup_weight{Read_From_File::powerup_initial_weight};
    int powerup_type{rand() % 2};
    int spawn_margin{static_cast<int> (window_ptr->getSize().x *
                                       Read_From_File::wall_width_factor + 1)};
    int score{};
    int score_timer{};
    sf::Text score_text{};
    sf::RectangleShape StartRec{};

    bool collide(Object* const&, Object* const&) const;
    void create_enemies();
    void create_pattern();
    void spawn_enemies();
    void create_powerups();
    void update_score();
    int get_lowest_highscore();
    void handle_collision(State* &);
    void open_menu() override;
};

#endif
