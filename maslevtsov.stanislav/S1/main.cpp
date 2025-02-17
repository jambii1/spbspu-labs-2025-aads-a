#include <iostream>
#include <list>
#include <utility>
#include <string>
#include <cctype>

int main()
{
  using pair_t = std::pair< std::string, std::list< unsigned int > >;
  using pair_list_t = std::list< pair_t >;

  pair_list_t list = {};
  std::string input_data = "";
  pair_t pair = {"", {}};
  bool is_first_pair = true, is_empty_input = true;
  while (!std::cin.eof()) {
    std::cin >> input_data;
    if (!std::isdigit(input_data[0]) || std::cin.eof()) {
      if (!is_first_pair) {
        list.push_back(pair);
      }
      pair = {input_data, {}};
      is_first_pair = false;
      continue;
    } else {
      pair.second.push_front(std::stoi(input_data));
      is_empty_input = false;
    }
  }

  if (is_empty_input) {
    std::cout << 0;
  } else {
    std::cout << (*list.begin()).first;
    for (auto i = ++list.cbegin(); i != list.cend(); ++i) {
      std::cout << ' ' << (*i).first;
    }
  }
  std::cout << '\n';
}
