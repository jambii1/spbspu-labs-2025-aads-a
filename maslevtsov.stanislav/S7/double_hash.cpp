#include "double_hash.hpp"
#include <boost/hash2/siphash.hpp>

size_t maslevtsov::StringDoubleHash::operator()(const std::string& string) const
{
  size_t h = std::hash< std::string >{}(string);
  boost::hash2::siphash_64 siph;
  siph.update(string.data(), string.size());
  return h ^ siph.result();
}

size_t maslevtsov::PairDoubleHash::operator()(const std::pair< std::string, std::string >& pair) const
{
  size_t h = std::hash< std::string >{}(pair.first);
  boost::hash2::siphash_64 siph;
  siph.update(pair.second.data(), pair.second.size());
  return h ^ siph.result();
}
