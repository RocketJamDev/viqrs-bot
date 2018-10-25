#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "../include/QR-Code-generator/QrCode.hpp"
#include "../include/QR-Code-generator/BitBuffer.hpp"
using qrcodegen::QrCode;

int main() {
  const char *text = "Hola, Vips!";              // User-supplied text
  QrCode::encodeText(text,  QrCode::Ecc::LOW);

  return 0;
}
