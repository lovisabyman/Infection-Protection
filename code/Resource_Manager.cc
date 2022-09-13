#include "Resource_Manager.h"
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <map>
#include <set>

using namespace std;

map<string, sf::Texture> Resource_Manager::graphic_resources{};
map<string, sf::Text>    Resource_Manager::text_resources{};
map<string, string>      Resource_Manager::string_resources{};
map<string, sf::Font>    Resource_Manager::font_resources{};

sf::Font Resource_Manager::font{};
sf::Text Resource_Manager::text{};


//Koden i load_graphics är delvis hämtad från föreläsning 8 av kursen TDDC76
//https://www.ida.liu.se/~TDDC76/2020/fo/slides/project/project.pdf
sf::Texture& Resource_Manager::load_graphics(string const& input_file)
{
  auto it{graphic_resources.find(input_file)};
  if (it == end(graphic_resources))
  {
      sf::Texture texture;
      texture.loadFromFile(input_file);
      it = graphic_resources.insert({input_file, texture}).first;
  }
  return (it->second);
}


sf::Text& Resource_Manager::load_text(string const& input_file)
{
    auto it{text_resources.find(input_file)};
    if (it == end(text_resources))
    {
        ifstream infile{input_file};
        string   file_contents{istreambuf_iterator<char>(infile),
                               istreambuf_iterator<char>()};
        text.setString(file_contents);
        it = text_resources.insert({input_file, text}).first;
        infile.close();
    }
    return (it->second);
}


sf::Font& Resource_Manager::load_font(string const& input_file)
{
    auto it{font_resources.find(input_file)};
    if (it == end(font_resources))
    {
        sf::Font font;
        font.loadFromFile(input_file);
        it = font_resources.insert({input_file, font}).first;
    }
    return (it->second);
}


string Resource_Manager::load_string(string const& input_file)
{
  auto it{string_resources.find(input_file)};
  if (it == end(string_resources))
  {
      ifstream     instream{input_file};
      stringstream instringstream;
      instringstream << instream.rdbuf();
      string instring{instringstream.str()};
      it = string_resources.insert({input_file, instring}).first;
      instream.close();
  }
  return (it->second);
}


void Resource_Manager::save_highscore(string const& name, int const score)
{
    ifstream highscore_stream{"Data/Highscore_List.txt"};
    int      curr_pos{};
    string   curr_name{};
    int      curr_score{};
    int      position{};
    while(highscore_stream >> curr_pos)
    {
        highscore_stream >> curr_name;
        highscore_stream >> curr_score;
        if (score > curr_score)
        {
            position = curr_pos;
            break;
        }
    }

    ifstream infile{"Data/Highscore_List.txt"};
    ofstream outfile{"Data/Highscore_temp.txt", std::ofstream::out};
    string   line;
    string   last_line;
    int      line_no{1};
    int      last_pos{};
    string   last_name{};
    int      last_score{};
    while(getline(infile, line))
    {
      if (line == "")
      {
          outfile << '\n';
      }
      else
      {
          if (line_no == position)
          {
             outfile << left << setw(8) << position << setw(22) << name << score << '\n';
          }
          else if (line_no < position)
          {
              outfile << line << '\n';
          }
          else if (line_no <= 10)
          {
              stringstream last_line_stream{last_line};
              last_line_stream >> last_pos;
              last_pos++;
              last_line_stream >> last_name;
              last_line_stream >> last_score;
              outfile << left << setw(8) << last_pos << setw(22) << last_name << last_score << '\n';
          }
          last_line = line;
          line_no ++;
      }
    }
    outfile.close();
    rename("Data/Highscore_temp.txt", "Data/Highscore_List.txt");
}
