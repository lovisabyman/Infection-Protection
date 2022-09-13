#ifndef READ_FROM_FILE_H
#define READ_FROM_FILE_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

struct Read_From_File
{
    Read_From_File();
    Read_From_File(Read_From_File const&) = delete;
    Read_From_File(Read_From_File&&)      = delete;
    Read_From_File& operator=(Read_From_File const&) = delete;
    Read_From_File& operator=(Read_From_File&&)      = delete;
    ~Read_From_File() = default;

    static std::string game_name;
    static int window_width;
    static int score_board_second_size_l;
    static int score_board_second_size_u;
    static int score_board_third_size_l;
    static int score_board_third_size_u;
    static int score_board_fourth_size_l;
    static int score_board_fourth_size_u;
    static int score_board_max_size;
    static int window_height;
    static int framerate;
    static int score_per_sec;
    static int enemy_initial_pattern_timer;
    static int enemy_initial_spawn_timer;
    static int enemy_initial_weight;
    static int enemy_pattern_interval;
    static int enemy_increase_weight;
    static int powerup_initial_weight;
    static int powerup_weight_max;
    static int powerup_weight_min;
    static int powerup_limit;
    static float wall_width_factor;

    static int bounce_ball;
    static int ball_encrease_size;
    static int decreas_divide;
    static int max_height_big_ball1;
    static int max_height_big_ball2;
    static int max_height_big_ball3;
    static int window_bottom;
    static int max_height_small_ball;
    static int rof_limit;
    static int projectile_speed;
    static int rof_timer;
    static int remaining_time_rof;
    static int remaining_time_shielded;
    static int time_powerup;
    static int speed_powerup;
    static int start_left_limit;
    static int end_left_limit;
    static int end_right_limit;
    static int powerup_left;
    static int powerup_right;
    static int number_divide1;
    static int number_divide2;
    static int number_divide3;
    static float player_width;
    static float player_height;

    static float origin_size_ball;
    static float reset_number;
    static float Gravity_Y;
    static float org_speed_big_ball;
    static float size_small_ball;
    static float org_speed_small_ball;
    static float speed_player;
    static float scale_projectile;
    static float rof_powerup_height;
    static float rof_powerup_width;
    static float rof_scale;
    static float powerup_beeline;
    static float shield_powerup_width;
    static float shield_powerup_height;
    static float scale_shield_powerup;

    static std::string ball_file;
    static std::string def_player;
    static std::string projectile_file;
    static std::string rof_player_pic;
    static std::string rof_powerup_pic;
    static std::string shield_powerup_pic;
    static std::string shield_player_pic;
    static std::string wall_pic;
    static std::string score_board;

    static std::string state_font;
    static std::string hi_font;
    static int hi_character_size;
    static int hi_text_pos_x;
    static int hi_text_pos_y;

    static std::string hem_font;

    static std::string em_font;
    static int em_score_character_size;
    static int em_score_text_pos_x;
    static int em_score_text_pos_y;

    static float nh_text_background_size_x;
    static float nh_text_background_size_y;
    static float nh_char_relative_size;
    static int   nh_nr_char_in_name;
    static float nh_message_pos_x;
    static float nh_message_pos_y;
    static int   nh_message_char_size;
    static float nh_warning_pos_y;
    static int   nh_warning_char_size;
    static int   nh_caret_blink_timer;
    static float nh_highscore_pos_x;
    static float nh_highscore_pos_y;
    static int   nh_highscore_char_size;
    static std::string nh_font;

    static std::string g_font;
    static int g_score_character_size;

    static int g_score_rect_initial_size_x;
    static int g_score_rect_2digit_size_x;
    static int g_score_rect_3digit_size_x;
    static int g_score_rect_4digit_size_x;
    static int g_score_rect_5digit_size_x;
    static int g_score_rect_size_y;
    static int g_score_rect_pos_x;
    static int g_score_rect_pos_y;
    static int g_score_rect_outline_thickness;

    static sf::Keyboard::Key move_right;
    static sf::Keyboard::Key move_left;
    static sf::Keyboard::Key shoot;

private:
    sf::Keyboard::Key string_to_key(std::string);
};

#endif
