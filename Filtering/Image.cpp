#include "Image.h"
#include "Array.h"
#include "Vec3.h"
#include "ppm.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>

namespace imaging

// Image:: me auto to tropo exw prosvasi se metavlites kai methodous tis klasis Image
{

    //diavase ta periexomena enos antikeimenou apo to file
    bool Image::load(const std::string& filename, const std::string& format)
    {

        std::string nameCopy = filename.substr(filename.size() - 3, 3); //apothikeuse stin metevliti nameCopy ta tria teleutaia grammata dil to ppm
        nameCopy.c_str(); //valta se pinaka charactirwn
        format.c_str(); //to idio kai gia to format
        for (int i = 0; i < 3; i++) {
            tolower(nameCopy[i]); //kanta mikra se periptwseis pou exw , Ppm PPm pPM pPM ktl
            tolower(format[i]);
        }

        if (format == nameCopy) { //ouasiastika an format == 'ppm'
            int w;
            int h;
            float* ImageData = ReadPPM(filename.c_str(), &w, &h);
            if (ImageData == NULL) { //an dn edwse tipota
                std::cout << "Error reading ppm file" << std::endl;
                return false;
            }

            this->buffer.resize(w * h);
            this->width = w;
            this->height = h;

            for (size_t i = 0, j = 0; i < (w) * (h)*3, j < (w) * (h); i += 3, j++) {
                this->buffer[j].r = ImageData[i];
                this->buffer[j].g = ImageData[i + 1];
                this->buffer[j].b = ImageData[i + 2];
            }
            //alliws mporouse na graftei os :
            //memcpy(this->buffer, ImageData, 3 * w * h * sizeof(float));
            return true;
        }
        else {
            std::cout << "Not a ppm file!" << std::endl;
            return false;
        }
    }
    //grapse ta periexomena enos antikeimenou sto file
    bool Image::save(const std::string& filename, const std::string& format)
    {

        std::string nameCopy = filename.substr(filename.size() - 3, 3); //apothikeuse stin metevliti nameCopy ta tria teleutaia grammata dil to ppm
        nameCopy.c_str(); //valta se pinaka charactirwn
        format.c_str(); //to idio kai gia to format
        for (int i = 0; i < 3; i++) {
            tolower(nameCopy[i]); //kanta mikra se periptwseis pou exw , Ppm PPm pPM pPM ktl
            tolower(format[i]);
        }
        if (nameCopy == format) {
            if (this->buffer.size() == 0) {
                std::cout << "Cannot save empty buffer" << std::endl;
                return false;
            }
            //einai 3 * width*height logw twn rgb pou einai 3 byte
            float* ImData = new float[3 * width * height];

            for (size_t i = 0, j = 0; i < (width) * (height)*3, j < (width) * (height); i += 3, j++) { // EDW EGINE 2/2 ALLAGH
                ImData[i] = this->buffer[j].r;
                ImData[i + 1] = this->buffer[j].g;
                ImData[i + 2] = this->buffer[j].b;
            }
            //i alliws
            //memcpy(ImData, this->buffer, width * height * sizeof(Color));
            return WritePPM(ImData, width, height, filename.c_str());
        }
        else {
            std::cout << "Not a ppm file!" << std::endl;
            return false;
        }
    }

} //namespace imaging
