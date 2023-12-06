#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream file("input.txt");

  if (!file.is_open()) {
    std::cout << "Error while opening file";
    return 1;
  }

  std::string line;
  int result = 0;
  while (std::getline(file, line)) {
    // \0 is a special value used to represent the end of a string
    // this is also called a null character
    // we use this since our chars cannot be null unless we make them pointers
    char f_digit = '\0';
    char l_digit = '\0';

    for (char c : line) {
      if (!std::isdigit(static_cast<unsigned char>(c))) {
        continue;
      }

      if (f_digit == '\0') {
        f_digit = c;
        l_digit = c;
      } else {
        l_digit = c;
      }
    }

    // char - '0' converts it to its integer value
    // https://stackoverflow.com/a/439589/3080244
    result += (f_digit - '0') * 10 + (l_digit - '0');
  }

  std::cout << result << std::endl;

  file.close();
  return 0;
}
