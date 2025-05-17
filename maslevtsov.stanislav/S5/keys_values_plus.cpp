#include "keys_values_plus.hpp"
#include <limits>
#include <stdexcept>

namespace {
  int sign(int value)
  {
    return (value > 0) ? 1 : ((value < 0) ? -1 : 0);
  }

  bool same_sign(int a, int b)
  {
    return sign(a) * sign(b) > 0;
  }
}

void maslevtsov::KeysValuesPlus::operator()(const std::pair< int, std::string >& value)
{
  constexpr int max_int = std::numeric_limits< int >::max();
  constexpr int min_int = std::numeric_limits< int >::min();
  if (same_sign(keys_sum, value.first) && (keys_sum > 0)) {
    if (max_int - keys_sum >= value.first) {
      keys_sum += value.first;
    } else {
      throw std::overflow_error("addition overflow");
    }
  } else if (same_sign(keys_sum, value.first) && (keys_sum < 0)) {
    if (min_int - keys_sum <= value.first) {
      keys_sum += value.first;
    } else {
      throw std::overflow_error("addition overflow");
    }
  } else if (!same_sign(keys_sum, value.first)) {
    keys_sum += value.first;
  }
  values += ' ' + value.second;
}
