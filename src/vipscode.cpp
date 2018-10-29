#include "vipscode.hpp"
#include <vector>

// initialize static members of class Vipscode
const std::string Vipscode::strIni = "ClubVipsApp?";
const char Vipscode::charEnd = 'A';

std::string Vipscode::getStringCode() const {
  return Vipscode::strIni + std::to_string(_number) + charEnd;
}

std::vector<Vipscode> Vipscode::getNextCodes(int num) const {
  std::vector<Vipscode> vcodes;

  for (int i = 0; i < num; i++) {
    vcodes.push_back(Vipscode(_number + i));
  }

  return vcodes;
}

std::vector<Vipscode> Vipscode::getPreviousCodes(int num) const {
  std::vector<Vipscode> vcodes;

  for (int i = 0; i < num; i++) {
    vcodes.push_back(Vipscode(_number - i));
  }

  return vcodes;
}
