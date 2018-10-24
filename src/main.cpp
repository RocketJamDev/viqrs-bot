#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

int test1(int a);

int main() {
  const char *text = "Hola, Vips!";              // User-supplied text
  const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  // Error correction level

  // Make and print the QR Code symbol
  const QrCode qr = QrCode::encodeText(text, errCorLvl);
  std::cout << qr.toSvgString(4) << std::endl;

  return 0;
}
