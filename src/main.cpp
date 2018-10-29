#include <iostream>
#include <string>
#include "vipscode.hpp"

//Qr library
#include "../lib/QR-Code-generator/QrCode.hpp"
#include "../lib/QR-Code-generator/BitBuffer.hpp"

//stb_image library
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write/stb_image_write.h"

using qrcodegen::QrCode;

#define PIX_PER_MODULE 10
#define BORDER 4

static void QRToImage(char const *filename, const QrCode &qr, int QrImageWidth, int QrImageHeight, unsigned char* rgb);
static void paintModule(const QrCode &qr, int x, int y, unsigned char* rgb);

int main(int argc, char **argv) {

  // put your code in the constructor
  Vipscode vc = Vipscode(100200522953);
  std::vector<Vipscode> vcodes = vc.getNextCodes(10);

  for(auto it = vcodes.begin(); it != vcodes.end(); it++) {
    const char *text = it->getStringCode().c_str();

    // encodes vips code to qr code
    QrCode qr = QrCode::encodeText(text,  QrCode::Ecc::LOW);

    // calculates size of QR image in QRToPixels
    int imageWidth = (qr.getSize() + BORDER * 2) * PIX_PER_MODULE;
    int imageHeight = imageWidth;

    // allocates memory for pixels array
    int PNGArraySize = imageWidth * imageHeight * 3;
    unsigned char* rgb = (unsigned char *) malloc (PNGArraySize);

    // creates qr image in data folder
    std::string file = "data/" + it->getStringCode() + ".png";
    const char *filename = file.c_str();
    QRToImage(filename, qr, imageWidth, imageHeight, rgb);

    free(rgb);

  }

  return 0;
}

static void QRToImage(char const *filename, const QrCode &qr, int imageWidth, int imageHeight, unsigned char* rgb) {

  int PNGArraySize = imageWidth * imageHeight * 3;

  // initialize array with white pixels
  for(int i = 0; i < PNGArraySize; i = i+3) {
    rgb[i] = 255;
    rgb[i+1] = 255;
    rgb[i+2] = 255;
  }

  // converts modules to pixels
	for (int y = 0; y < qr.getSize(); y++) {
		for (int x = 0; x < qr.getSize(); x++) {
      if (qr.getModule(x, y)) {
          paintModule(qr, x + BORDER, y + BORDER, rgb);
      }
		}
	}

  // wirtes in file
  stbi_write_png(filename, imageWidth, imageHeight, 3, rgb, imageWidth * 3);
}

static void paintModule(const QrCode &qr, int x, int y, unsigned char* rgb) {
    for(int i = y * PIX_PER_MODULE; i < y * PIX_PER_MODULE + PIX_PER_MODULE; i++) {
        for (int j = x * PIX_PER_MODULE * 3; j < (x * PIX_PER_MODULE * 3 + (PIX_PER_MODULE * 3)); j = j + 3) {

            // index to 1D
            int index = (i * ((qr.getSize() + BORDER * 2) * PIX_PER_MODULE) * 3) + j;

            // paint black pixels
            rgb[index] = 0;
            rgb[index+1] = 0;
            rgb[index+2] = 0;
        }
    }
}
