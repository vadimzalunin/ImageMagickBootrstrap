//============================================================================
// Name        : PrintPixelsExample.cpp
// Author      : vadim
// Version     :
// Copyright   :
// Description : Prints pixels color to stdout using cached and direct access.
//============================================================================
#include <Magick++.h>
#include <iostream>
#include <string>

using namespace std;
using namespace Magick;

int main(int argc, char **argv) {
	InitializeMagick(*argv);

	Image image;
	try {
		string imageFilePath = "src/exit.png";
		cout << "Reading image: " << imageFilePath << endl;
		image.read(imageFilePath);

		unsigned int width = image.columns();
		unsigned int height = image.rows();
		cout << "Image size: width=" << width << ", height=" << height << endl;

		// cached region of the image:
		PixelPacket *pixels = image.getPixels(0, 0, width, height);

		for (unsigned int i = 0; i < width * height; i++) {
			// access pixels in the cached region:
			cout << i << "\t" << pixels[i].red * 256 / MaxRGB << "\t"
					<< pixels[i].green * 256 / MaxRGB << "\t"
					<< pixels[i].blue * 256 / MaxRGB << endl;

			// access pixels directly from image:
			const int x = i % width;
			const int y = i / width;
			const Color color = image.pixelColor(x, y);
			cout << i << "\t" << color.redQuantum() * 256 / MaxRGB << "\t"
					<< color.greenQuantum() * 256 / MaxRGB << "\t"
					<< color.blueQuantum() * 256 / MaxRGB << endl;
		}
		cout << "\n";
	} catch (Exception &error_) {
		cout << "Caught exception: " << error_.what() << endl;
		return 1;
	}
	return 0;
}
