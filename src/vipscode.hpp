//vipscode.hpp
//ClubVipsApp?xxxxxxxxxxxxA
#include <string>
#include <vector>
#include <iostream>

class Vipscode {

public:

  static const std::string strIni;
  static const std::string charEnd;

  Vipscode() {}
  Vipscode(long int number) : _number(number) { }
  Vipscode(std::string code);
  long int getNumber() const { return _number; }
  void setNumber(long int number) { _number = number; }
  std::string getStringCode() const;
  std::vector<Vipscode> getNextCodes(int num) const;
  std::vector<Vipscode> getPreviousCodes(int num) const;

private:
  long int _number;
};
