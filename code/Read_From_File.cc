#include "Read_From_File.h"
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

int Read_From_File::bounce_ball{};
int Read_From_File::ball_encrease_size{};
int Read_From_File::decreas_divide{};
int Read_From_File::max_height_big_ball1{};
int Read_From_File::max_height_big_ball2{};
int Read_From_File::max_height_big_ball3{};
int Read_From_File::window_bottom{};
int Read_From_File::max_height_small_ball{};
int Read_From_File::rof_limit{};
int Read_From_File::projectile_speed{};
int Read_From_File::rof_timer{};
int Read_From_File::remaining_time_rof{};
int Read_From_File::remaining_time_shielded{};
int Read_From_File::time_powerup{};
int Read_From_File::speed_powerup{};
int Read_From_File::start_left_limit{};
int Read_From_File::end_left_limit{};
int Read_From_File::end_right_limit{};
int Read_From_File::powerup_right{};
int Read_From_File::powerup_left{};
int Read_From_File::number_divide1{};
int Read_From_File::number_divide2{};
int Read_From_File::number_divide3{};

float Read_From_File::player_width{};
float Read_From_File::player_height{};
float Read_From_File::reset_number{};
float Read_From_File::origin_size_ball{};
float Read_From_File::Gravity_Y{};
float Read_From_File::org_speed_big_ball{};
float Read_From_File::size_small_ball{};
float Read_From_File::org_speed_small_ball{};
float Read_From_File::speed_player{};
float Read_From_File::scale_projectile{};
float Read_From_File::rof_powerup_width{};
float Read_From_File::rof_powerup_height{};
float Read_From_File::rof_scale{};
float Read_From_File::powerup_beeline{};
float Read_From_File::shield_powerup_width{};
float Read_From_File::shield_powerup_height{};
float Read_From_File::scale_shield_powerup{};
float Read_From_File::wall_width_factor{};

std::string Read_From_File::ball_file{};
std::string Read_From_File::def_player{};
std::string Read_From_File::projectile_file{};
std::string Read_From_File::rof_player_pic{};
std::string Read_From_File::rof_powerup_pic{};
std::string Read_From_File::shield_powerup_pic{};
std::string Read_From_File::shield_player_pic{};
std::string Read_From_File::wall_pic{};

int Read_From_File::window_width{};
int Read_From_File::window_height{};
int Read_From_File::framerate{};
std::string Read_From_File::game_name{};
std::string Read_From_File::score_board{};
int Read_From_File::score_per_sec{};
int Read_From_File::enemy_initial_pattern_timer{};
int Read_From_File::enemy_initial_spawn_timer{};
int Read_From_File::enemy_initial_weight{};
int Read_From_File::enemy_pattern_interval{};
int Read_From_File::enemy_increase_weight{};
int Read_From_File::powerup_initial_weight{};
int Read_From_File::powerup_weight_max{};
int Read_From_File::powerup_weight_min{};
int Read_From_File::powerup_limit{};
int Read_From_File::score_board_second_size_l{};
int Read_From_File::score_board_second_size_u{};
int Read_From_File::score_board_third_size_l{};
int Read_From_File::score_board_third_size_u{};
int Read_From_File::score_board_fourth_size_l{};
int Read_From_File::score_board_fourth_size_u{};
int Read_From_File::score_board_max_size{};

//sm_ = Start_Menu
//g_ = Game
//him_ = Highscore_Menu
//hem_ = Help_Menu
//nh_ = New_Highscore
//em_ = End_Menu

std::string Read_From_File::state_font{};
std::string Read_From_File::hi_font{};

int Read_From_File::hi_character_size{};
int Read_From_File::hi_text_pos_x{};
int Read_From_File::hi_text_pos_y{};

float Read_From_File::nh_text_background_size_x{};
float Read_From_File::nh_text_background_size_y{};
float Read_From_File::nh_char_relative_size{};
int   Read_From_File::nh_nr_char_in_name{};
float Read_From_File::nh_message_pos_x{};
float Read_From_File::nh_message_pos_y{};
int   Read_From_File::nh_message_char_size{};
float Read_From_File::nh_warning_pos_y{};
int   Read_From_File::nh_warning_char_size{};
int   Read_From_File::nh_caret_blink_timer{};
float Read_From_File::nh_highscore_pos_x{};
float Read_From_File::nh_highscore_pos_y{};
int   Read_From_File::nh_highscore_char_size{};
std::string Read_From_File::nh_font{};

std::string Read_From_File::hem_font{};
std::string Read_From_File::em_font{};
int Read_From_File::em_score_character_size{};
int Read_From_File::em_score_text_pos_x{};
int Read_From_File::em_score_text_pos_y{};


std::string Read_From_File::g_font{};
int Read_From_File::g_score_character_size{};

int Read_From_File::g_score_rect_initial_size_x{};
int Read_From_File::g_score_rect_2digit_size_x{};
int Read_From_File::g_score_rect_3digit_size_x{};
int Read_From_File::g_score_rect_4digit_size_x{};
int Read_From_File::g_score_rect_5digit_size_x{};
int Read_From_File::g_score_rect_size_y{};
int Read_From_File::g_score_rect_pos_x{};
int Read_From_File::g_score_rect_pos_y{};
int Read_From_File::g_score_rect_outline_thickness{};

sf::Keyboard::Key Read_From_File::move_right{};
sf::Keyboard::Key Read_From_File::move_left{};
sf::Keyboard::Key Read_From_File::shoot{};


Read_From_File::Read_From_File()
{
    std::ifstream infile;
    infile.open("Data/data.txt");
    std::string type;
    std::string variable;
    std::string value;

    std::map<std::string, int>         int_map;
    std::map<std::string, float>       float_map;
    std::map<std::string, std::string> string_map;
    std::map<std::string, sf::Keyboard::Key> key_map;

    while (infile)
    {
        infile >> type;
        infile >> variable;
        infile >> value;
        if (type == "int")
        {
            int_map[variable] = std::stoi(value);
        }
        if (type == "string")
        {
            string_map[variable] = value;
        }
        if (type == "float")
        {
            float_map[variable] = std::stof(value);
        }
        if (type == "key")
        {
            std::for_each(value.begin(), value.end(), [](char & c)
                          {c = ::tolower(c);});
            key_map[variable] = string_to_key(value);
        }
    }
    Read_From_File::bounce_ball           = int_map["bounce_ball"];
    Read_From_File::ball_encrease_size    = int_map["ball_encrease_size"];
    Read_From_File::decreas_divide        = int_map["decreas_divide"];
    Read_From_File::max_height_big_ball1  = int_map["max_height_big_ball1"];
    Read_From_File::max_height_big_ball2  = int_map["max_height_big_ball2"];
    Read_From_File::max_height_big_ball3  = int_map["max_height_big_ball3"];
    Read_From_File::window_bottom         = int_map["window_bottom"];
    Read_From_File::max_height_small_ball = int_map["max_height_small_ball"];
    Read_From_File::rof_limit             = int_map["rof_limit"];
    Read_From_File::projectile_speed      = int_map["projectile_speed"];
    Read_From_File::rof_timer             = int_map["rof_timer"];
    Read_From_File::remaining_time_rof    = int_map["remaining_time_rof"];
    Read_From_File::remaining_time_shielded =
                    int_map["remaining_time_shielded"];
    Read_From_File::time_powerup          = int_map["time_powerup"];
    Read_From_File::speed_powerup         = int_map["speed_powerup"];
    Read_From_File::start_left_limit      = int_map["start_left_limit"];
    Read_From_File::end_left_limit        = int_map["end_left_limit"];
    Read_From_File::end_right_limit       = int_map["end_right_limit"];
    Read_From_File::powerup_right         = int_map["powerup_right"];
    Read_From_File::powerup_left          = int_map["powerup_left"];
    Read_From_File::player_width          = float_map["player_width"];
    Read_From_File::player_height         = float_map["player_height"];
    Read_From_File::number_divide1        = int_map["number_divide1"];
    Read_From_File::number_divide2        = int_map["number_divide2"];
    Read_From_File::number_divide3        = int_map["number_divide3"];

    Read_From_File::reset_number          = float_map["reset"];
    Read_From_File::origin_size_ball      = float_map["origin_size_ball"];
    Read_From_File::Gravity_Y             = float_map["Gravity_Y"];
    Read_From_File::org_speed_big_ball    = float_map["org_speed_big_ball"];
    Read_From_File::size_small_ball       = float_map["size_small_ball"];
    Read_From_File::org_speed_small_ball  = float_map["org_speed_small_ball"];
    Read_From_File::speed_player          = float_map["speed_player"];
    Read_From_File::scale_projectile      = float_map["scale_projectile"];
    Read_From_File::rof_powerup_width     = float_map["rof_powerup_width"];
    Read_From_File::rof_powerup_height    = float_map["rof_powerup_height"];
    Read_From_File::rof_scale             = float_map["rof_scale"];
    Read_From_File::powerup_beeline       = float_map["powerup_beeline"];
    Read_From_File::shield_powerup_width  = float_map["shield_powerup_width"];
    Read_From_File::shield_powerup_height = float_map["shield_powerup_height"];
    Read_From_File::scale_shield_powerup  = float_map["scale_shield_powerup"];

    Read_From_File::ball_file          = string_map["ball_file"];
    Read_From_File::def_player         = string_map["def_player"];
    Read_From_File::projectile_file    = string_map["projectile_file"];
    Read_From_File::rof_player_pic     = string_map["rof_player_pic"];
    Read_From_File::rof_powerup_pic    = string_map["rof_powerup_pic"];
    Read_From_File::shield_powerup_pic = string_map["shield_powerup_pic"];
    Read_From_File::shield_player_pic  = string_map["shield_player_pic"];
    Read_From_File::wall_pic           = string_map["wall_pic"];

    Read_From_File::window_width           = int_map["window_width"];
    Read_From_File::window_height          = int_map["window_height"];
    Read_From_File::framerate              = int_map["framerate"];
    Read_From_File::game_name              = string_map["game_name"];
    Read_From_File::score_board            = string_map["score_board"];
    Read_From_File::score_per_sec          = int_map["score_per_sec"];
    Read_From_File::wall_width_factor      = float_map["wall_width_factor"];
    Read_From_File::enemy_initial_weight   = int_map["enemy_initial_weight"];
    Read_From_File::enemy_pattern_interval = int_map["enemy_pattern_interval"];
    Read_From_File::enemy_increase_weight  = int_map["enemy_increase_weight"];
    Read_From_File::powerup_initial_weight = int_map["powerup_initial_weight"];
    Read_From_File::powerup_weight_max     = int_map["powerup_weight_max"];
    Read_From_File::powerup_weight_min     = int_map["powerup_weight_min"];
    Read_From_File::powerup_limit          = int_map["powerup_limit"];
    Read_From_File::enemy_initial_pattern_timer =
                    int_map["enemy_initial_pattern_timer"];
    Read_From_File::enemy_initial_spawn_timer   =
                    int_map["enemy_initial_spawn_timer"];

    Read_From_File::state_font        = string_map["state_font"];
    Read_From_File::hi_font           = string_map["hi_font"];
    Read_From_File::hi_character_size = int_map["hi_character_size"];
    Read_From_File::hi_text_pos_x     = int_map["hi_text_pos_x"];
    Read_From_File::hi_text_pos_y     = int_map["hi_text_pos_y"];

    Read_From_File::nh_text_background_size_x =
                    float_map["nh_text_background_size_x"];
    Read_From_File::nh_text_background_size_y =
                    float_map["nh_text_background_size_y"];
    Read_From_File::nh_char_relative_size   =
                    float_map["nh_char_relative_size"];
    Read_From_File::nh_nr_char_in_name      = int_map["nh_nr_char_in_name"];
    Read_From_File::nh_message_pos_x        = float_map["nh_message_pos_x"];
    Read_From_File::nh_message_pos_y        = float_map["nh_message_pos_y"];
    Read_From_File::nh_message_char_size    = int_map["nh_message_char_size"];
    Read_From_File::nh_warning_pos_y        = float_map["nh_warning_pos_y"];
    Read_From_File::nh_warning_char_size    = int_map["nh_warning_char_size"];
    Read_From_File::nh_caret_blink_timer    = int_map["nh_caret_blink_timer"];
    Read_From_File::nh_highscore_pos_x      = float_map["nh_highscore_pos_x"];
    Read_From_File::nh_highscore_pos_y      = float_map["nh_highscore_pos_y"];
    Read_From_File::nh_highscore_char_size  = int_map["nh_highscore_char_size"];
    Read_From_File::score_board_second_size_l =
                    int_map["score_board_second_size_l"];
    Read_From_File::score_board_second_size_u =
                    int_map["score_board_second_size_u"];
    Read_From_File::score_board_third_size_l  =
                    int_map["score_board_third_size_l"];
    Read_From_File::score_board_third_size_u  =
                    int_map["score_board_third_size_u"];
    Read_From_File::score_board_fourth_size_l =
                    int_map["score_board_fourth_size_l"];
    Read_From_File::score_board_fourth_size_u =
                    int_map["score_board_fourth_size_u"];
    Read_From_File::score_board_max_size      =
                    int_map["score_board_max_size"];
    Read_From_File::nh_font  = string_map["nh_font"];


    Read_From_File::hem_font = string_map["hem_font"];

    Read_From_File::em_font                 = string_map["em_font"];
    Read_From_File::em_score_character_size =
                    int_map["em_score_character_size"];
    Read_From_File::em_score_text_pos_x     = int_map["em_score_text_pos_x"];
    Read_From_File::em_score_text_pos_y     = int_map["em_score_text_pos_y"];


    Read_From_File::g_font                 = string_map["g_font"];
    Read_From_File::g_score_character_size = int_map["g_score_character_size"];

    Read_From_File::g_score_rect_initial_size_x    =
                    int_map["g_score_rect_initial_size_x"];
    Read_From_File::g_score_rect_2digit_size_x     =
                    int_map["g_score_rect_2digit_size_x"];
    Read_From_File::g_score_rect_3digit_size_x     =
                    int_map["g_score_rect_3digit_size_x"];
    Read_From_File::g_score_rect_4digit_size_x     =
                    int_map["g_score_rect_4digit_size_x"];
    Read_From_File::g_score_rect_5digit_size_x     =
                    int_map["g_score_rect_5digit_size_x"];
    Read_From_File::g_score_rect_size_y            =
                    int_map["g_score_rect_size_y"];
    Read_From_File::g_score_rect_pos_x             =
                    int_map["g_score_rect_pos_x"];
    Read_From_File::g_score_rect_pos_y             =
                    int_map["g_score_rect_pos_y"];
    Read_From_File::g_score_rect_outline_thickness =
                    int_map["g_score_rect_outline_thickness"];

    Read_From_File::move_right = key_map["move_right"];
    Read_From_File::move_left  = key_map["move_left"];
    Read_From_File::shoot      = key_map["shoot"];
}


sf::Keyboard::Key Read_From_File::string_to_key(std::string value)
{
    sf::Keyboard::Key key{};
    if (value == "right")
    {
        key = sf::Keyboard::Key::Right;
    }
    if (value == "left")
    {
        key = sf::Keyboard::Key::Left;
    }
    if (value == "up")
    {
        key = sf::Keyboard::Key::Up;
    }
    if (value == "down")
    {
        key = sf::Keyboard::Key::Down;
    }
    if (value == "q")
    {
        key = sf::Keyboard::Key::Q;
    }
    if (value == "w")
    {
        key = sf::Keyboard::Key::W;
    }
    if (value == "e")
    {
        key = sf::Keyboard::Key::E;
    }
    if (value == "r")
    {
        key = sf::Keyboard::Key::R;
    }
    if (value == "t")
    {
        key = sf::Keyboard::Key::T;
    }
    if (value == "y")
    {
        key = sf::Keyboard::Key::Y;
    }
    if (value == "u")
    {
        key = sf::Keyboard::Key::U;
    }
    if (value == "i")
    {
        key = sf::Keyboard::Key::I;
    }
    if (value == "o")
    {
        key = sf::Keyboard::Key::O;
    }
    if (value == "p")
    {
        key = sf::Keyboard::Key::P;
    }
    if (value == "a")
    {
        key = sf::Keyboard::Key::A;
    }
    if (value == "s")
    {
        key = sf::Keyboard::Key::S;
    }
    if (value == "d")
    {
        key = sf::Keyboard::Key::D;
    }
    if (value == "f")
    {
        key = sf::Keyboard::Key::F;
    }
    if (value == "g")
    {
        key = sf::Keyboard::Key::G;
    }
    if (value == "h")
    {
        key = sf::Keyboard::Key::H;
    }
    if (value == "j")
    {
        key = sf::Keyboard::Key::J;
    }
    if (value == "k")
    {
        key = sf::Keyboard::Key::K;
    }
    if (value == "l")
    {
        key = sf::Keyboard::Key::L;
    }
    if (value == "z")
    {
        key = sf::Keyboard::Key::Z;
    }
    if (value == "x")
    {
        key = sf::Keyboard::Key::X;
    }
    if (value == "x")
    {
        key = sf::Keyboard::Key::X;
    }
    if (value == "c")
    {
        key = sf::Keyboard::Key::C;
    }
    if (value == "v")
    {
        key = sf::Keyboard::Key::V;
    }
    if (value == "b")
    {
        key = sf::Keyboard::Key::B;
    }
    if (value == "n")
    {
        key = sf::Keyboard::Key::N;
    }
    if (value == "m")
    {
        key = sf::Keyboard::Key::M;
    }
    if (value == "1")
    {
        key = sf::Keyboard::Key::Num1;
    }
    if (value == "2")
    {
        key = sf::Keyboard::Key::Num2;
    }
    if (value == "3")
    {
        key = sf::Keyboard::Key::Num3;
    }
    if (value == "4")
    {
        key = sf::Keyboard::Key::Num4;
    }
    if (value == "5")
    {
        key = sf::Keyboard::Key::Num5;
    }
    if (value == "6")
    {
        key = sf::Keyboard::Key::Num6;
    }
    if (value == "7")
    {
        key = sf::Keyboard::Key::Num7;
    }
    if (value == "8")
    {
        key = sf::Keyboard::Key::Num8;
    }
    if (value == "9")
    {
        key = sf::Keyboard::Key::Num9;
    }
    if (value == "space")
    {
        key = sf::Keyboard::Key::Space;
    }

    return key;
}
