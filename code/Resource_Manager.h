#ifndef RESOURCE_MANAGER_HEADER_H
#define RESOURCE_MANAGER_HEADER_H

#include <map>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Resource_Manager
{
public:
  Resource_Manager() {}
  Resource_Manager(Resource_Manager const&) = delete;
  Resource_Manager(Resource_Manager&&)      = delete;
  Resource_Manager& operator=(Resource_Manager const&) = delete;
  Resource_Manager& operator=(Resource_Manager&&)      = delete;
  ~Resource_Manager() = default;

  static sf::Texture& load_graphics(std::string const& input_file);
  static sf::Text&    load_text(std::string const& input_file);
  static sf::Font&    load_font(std::string const& input_file);
  static std::string  load_string(std::string const& input_file);
  static void         save_highscore(std::string const& name, int const score);

private:
  static std::map<std::string, sf::Texture> graphic_resources;
  static std::map<std::string, sf::Text>    text_resources;
  static std::map<std::string, std::string> string_resources;
  static std::map<std::string, sf::Font>    font_resources;
  static sf::Font font;
  static sf::Text text;
};

#endif
