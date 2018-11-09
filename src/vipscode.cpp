#include "vipscode.hpp"
#include <vector>
#include <iostream>

// initialize static members of class Vipscode
const std::string Vipscode::strIni = "ClubVipsApp?";
const std::string Vipscode::charEnd = "A";

Vipscode::Vipscode(std::string code) {
  
    std::string::size_type i = code.find(strIni);

    if (i != std::string::npos)
        code.erase(i, strIni.length());

    i = code.find(charEnd);

    if (i != std::string::npos)
        code.erase(i, code.length());

    _number = stol(code);
    std::cout << _number << std::endl;
}

std::string Vipscode::getStringCode() const {
  return Vipscode::strIni + std::to_string(_number) + charEnd;
}

std::vector<Vipscode> Vipscode::getNextCodes(int num) const {
  std::vector<Vipscode> vcodes;

  for (int i = 1; i <= num; i++) {
    vcodes.push_back(Vipscode(_number + i));
  }

  return vcodes;
}

std::vector<Vipscode> Vipscode::getPreviousCodes(int num) const {
  std::vector<Vipscode> vcodes;

  for (int i = 1; i < num; i++) {
    vcodes.push_back(Vipscode(_number - i));
  }

  return vcodes;
}
