//vipscode.hpp
//ClubVipsApp?xxxxxxxxxxxxA
#include <string>
#include <vector>

class Vipscode {

public:

  static const std::string strIni;
  static const char charEnd;

  Vipscode() {}
  Vipscode(long int number) : _number(number) {}
  long int getNumber() const { return _number; }
  void setNumber(long int number) { _number = number; }
  std::string getStringCode() const;
  std::vector<Vipscode> getNextCodes(int num) const;

private:
  long int _number;
};
