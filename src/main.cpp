#include <iostream>

//Qr library
#include "../include/QR-Code-generator/QrCode.hpp"
#include "../include/QR-Code-generator/BitBuffer.hpp"

//stb_image library
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write/stb_image_write.h"

using qrcodegen::QrCode;

#define PIX_PER_MODULE 49
#define BORDER 4

static void QRToPixels(const QrCode &qr, unsigned char* rgb, const int QrImageSize);

int main() {
  const char *text = "Hola, Vips!";              // User-supplied text
  QrCode qr = QrCode::encodeText(text,  QrCode::Ecc::LOW);

  // calculates size of QR image
  int QrImageSize = (qr.getSize() + BORDER) * (qr.getSize() + BORDER) * 3 * PIX_PER_MODULE;

  std::cout << "Tamaño array: " << qr.getSize();

  // allocates memory for pixels array
  unsigned char* rgb = (unsigned char *) malloc (QrImageSize);

  // creates array of pixels
  QRToPixels(qr, rgb, QrImageSize);

  return 0;
}

static void QRToPixels(const QrCode &qr, unsigned char* rgb, const int QrImageSize) {
  // initialize array with white pixels
  for(int i = 0; i < QrImageSize - 3; i = i+3) {
    rgb[i] = 255;
    rgb[i+1] = 255;
    rgb[i+2] = 255;
  }

/*
	for (int y = -border; y < qr.getSize() + border; y++) {
		for (int x = -border; x < qr.getSize() + border; x++) {
			if (qr.getModule(x, y)) {

      }
		}
		std::cout << std::endl;
	}*/

  stbi_write_bmp("demo.bmp", (qr.getSize() + BORDER) * 7, (qr.getSize() + BORDER) * 7, 3, rgb);
}
