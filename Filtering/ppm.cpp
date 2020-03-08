#ifndef _PPM
#define _PPM

#include "ppm.h"
#include "Image.h"
#include "Vec3.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>

namespace imaging {

    float* ReadPPM(const char* filename, int* w, int* h)
    {
        std::fstream file(filename, std::ios::in | std::ios::binary);
        if (!file.is_open()) { //elegxos gia anoigma arxeiou
            return NULL;
        }

        std::string str;
        file >> str;
        if (str != "P6") {
            std::cout << "This is not a P6 file!" << std::endl;
            return NULL;
        }

        int width, height, pixels;
        file >> width >> height >> pixels;
        *w = width;
        *h = height;

        if (w == NULL || width <= 0 || h == NULL || height <= 0) {
            std::cout << "Error! Width and Height of the image are not valid!" << std::endl;
            return NULL;
        }
        if (pixels > 255 || pixels <= 0) {
            std::cout << "Error! Max value of pixels is not valid!" << std::endl;
            return NULL;
        }

        //to seekg: Sets the position where the next character is to be inserted into the output stream
        //to cur  : current position within sequence
        //to kanoume gia na paralipsei  ti teliki grammi i to keno sto telos tis kefalidas
        file.seekg(1, std::ios::cur);
        //pinaka 3 byte-> 1 pixel
        unsigned char pix[3];
        float* ppm_array = new float[3 * width * height];

        int j = 0;
        for (int i = 0; i < width * height; ++i) {
            file.read((char*)pix, 3); //diavazw kathe pixel i alliws 3 byte ena ena os xaraktires

            ppm_array[j] = int(pix[0]) / 255.f; //ta metatrepw se float
            ppm_array[j + 1] = int(pix[1]) / 255.f;
            ppm_array[j + 2] = int(pix[2]) / 255.f;

            j += 3;
        }

        return ppm_array;
    }

    bool WritePPM(const float* data, int w, int h, const char* filename)
    {
        if (data == NULL) {
            return false;
        }
        else {
            std::fstream file(filename, std::ios::out | std::ios::binary);
            file << "P6" << std::endl
                 << w << " "
                 << h << std::endl
                 << "255" << std::endl;

            unsigned char r, g, b;
            int j = 0;
            for (int i = 0; i < w * h; i++) { //pairnw kathe pixel tis eikonas kai
                //kai to fernw se morfi byte
                r = data[j] * 255;
                g = data[j + 1] * 255;
                b = data[j + 2] * 255;

                file << r << g << b;
                j += 3;
            }
            file.close();
        }
    }

} //namespace imaging

#endif
