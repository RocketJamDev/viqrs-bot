#include <iostream>
#include <string.h>

//Qr library
#include "../include/QR-Code-generator/QrCode.hpp"
#include "../include/QR-Code-generator/BitBuffer.hpp"

//stb_image library
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write/stb_image_write.h"

using qrcodegen::QrCode;

#define PIX_PER_MODULE 3
#define BORDER 4

static void QRToPixels(const QrCode &qr, unsigned char* rgb, int QrImageWidth, int QrImageHeight);
static void paintModule(const QrCode &qr, int x, int y, unsigned char* rgb);

int main() {
  const char *text = "Hola, Vips!";              // User-supplied text
  QrCode qr = QrCode::encodeText(text,  QrCode::Ecc::LOW);

  // calculates size of QR image
  int QrImageWidth = (qr.getSize() + BORDER * 2) * PIX_PER_MODULE * 3;
  int QrImageHeight = (qr.getSize() + BORDER * 2) * PIX_PER_MODULE;

  int QrImageSize = QrImageWidth * QrImageHeight;
  std::cout << QrImageSize << std::endl;


  // allocates memory for pixels array
  unsigned char* rgb = (unsigned char *) malloc (QrImageSize);

  // creates array of pixels
  QRToPixels(qr, rgb, QrImageWidth, QrImageHeight);

  free(rgb);

  return 0;
}

static void QRToPixels(const QrCode &qr, unsigned char* rgb, int QrImageWidth, int QrImageHeight) {

  int count = 0;
  int QrImageSize = QrImageWidth * QrImageHeight;
  // initialize array with white pixels
  for(int i = 0; i < QrImageSize - 3; i = i+3) {
    rgb[i] = 255;
    rgb[i+1] = 255;
    rgb[i+2] = 255;
    count += 3;
  }

  std::cout << "Tamaño de la array: " << count << std::endl;

  //x columns, y rows
	for (int y = -BORDER; y < qr.getSize() + BORDER; y++) {
		for (int x = -BORDER; x < qr.getSize() + BORDER; x++) {
      if (qr.getModule(x, y)) {
          paintModule(qr, x, y, rgb);
      }
		}
	}

  std::cout << count << std::endl;

  stbi_write_bmp("demo.bmp", (qr.getSize() + BORDER * 2) * PIX_PER_MODULE, (qr.getSize() + BORDER * 2) * PIX_PER_MODULE, 3, rgb);
}

static void paintModule(const QrCode &qr, int x, int y, unsigned char* rgb) {
    for(int i = y * PIX_PER_MODULE; i < y * PIX_PER_MODULE + PIX_PER_MODULE; i++) {
        std::cout << "Vuelta i: " << i << std::endl;
        for (int j = x * PIX_PER_MODULE * 3; j < (x * PIX_PER_MODULE * 3 + (PIX_PER_MODULE * 3)); j = j + 3) {
            std::cout << "Vuelta j: " << j << std::endl;
            std::cout << "Painted: \t(" << j << ", " << i << ")" << std::endl;
            std::cout << "\t\t\t(" << j+1 << ", " << i << ")" << std::endl;
            std::cout << "\t\t\t(" << j+2 << ", " << i << ")" << std::endl;
            std::cout << std::endl;

            // index to 1D
            int index = (i * ((qr.getSize() + BORDER * 2) * PIX_PER_MODULE) * 3) + j;

            //std::cout << "DEBUG" << std::endl;
            std::cout << "Indice: " << index << std::endl;
            std::cout << "Indice: " << index + 1 << std::endl;
            std::cout << "Indice: " << index + 2 << std::endl;

            // paint black pixels
            rgb[index] = 0;
            rgb[index+1] = 0;
            rgb[index+2] = 0;
        }
    }
}
