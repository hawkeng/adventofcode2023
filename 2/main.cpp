#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

bool has_valid_games(const std::string &records_str,
                     const std::unordered_map<std::string, int> &color_ncubes) {
  std::string n_games = "";
  std::string color = "";
  std::string *cur_str = &n_games;
  for (int i = 0; i < records_str.size(); i++) {
    char c = records_str[i];
    // need to check the length of n_games since often the first character
    // it's an space
    if (c == ' ' && n_games.length() > 0) {
      cur_str = &color;
      continue;
    }

    if (c != ',' && c != ';') {
      *cur_str += c;
      // need to check if this is the last character
      // if it is we don't want to skip this cycle
      // so we can process the last record
      if (i != records_str.size() - 1) {
        continue;
      }
    }

    if (std::stoi(n_games) > color_ncubes.at(color)) {
      return false;
    }

    n_games = "";
    color = "";
    cur_str = &n_games;
  }

  return true;
}

/**
 * Determine which games would have been possible if the bag had been loaded
 * with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of
 * the IDs of those games?
 */
int main() {
  std::fstream file("input.txt");
  if (!file.is_open()) {
    std::cout << "Error while opening input file" << std::endl;
    return 1;
  }

  std::unordered_map<std::string, int> color_ncubes;
  color_ncubes["red"] = 12;
  color_ncubes["green"] = 13;
  color_ncubes["blue"] = 14;

  int possible_game_ids_sum = 0;

  // I'm purposefuly avoiding regex parsing
  std::string line;
  while (std::getline(file, line)) {
    std::string game_part = line.substr(0, line.find(':'));

    std::string ignore;
    int game_id;
    std::stringstream ss(game_part);
    ss >> ignore >> game_id;

    std::string records_part =
        line.substr(line.find(":") + 2, line.length() - 1);
    if (has_valid_games(records_part, color_ncubes)) {
      possible_game_ids_sum += game_id;
    }
  }

  std::cout << "Result: " << possible_game_ids_sum << std::endl;

  file.close();
  return 0;
}
