#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "Color.h"
#include "Image.h"
#include "ppm.h"

namespace imaging

// Image:: me auto to tropo exw prosvasi se metavlites kai methodous tis klasis Image
{
    Color* Image::getRawDataPtr()
    {
        return buffer;
    }

    Color Image::getPixel(unsigned int x, unsigned int y) const
    {
        if (x > width || y > height) { // an i eikona einai 1000 x 1000 kai zitisoume to pixel x kai y megalitera einai out of bounds
            return imaging::Color(0, 0, 0); //diladi an oi sintetagmenes ksepernane to width kai to heigth
                                            //epestrepse mauro
        }
        else {
            int pos = x + (y * width);  //koita set pixel eksigisi
            return buffer[pos];
        }
    }

    void Image::setPixel(unsigned int x, unsigned int y, Color& value)
    {
        if (x > width || y > height) {
            std::cout << "The cordinates are out of bounds" << std::endl;
            return;
        }
        else {
            int pos = x + (y * width); //px an thelw to 4o pixel ,se enan "disdiastato" 6x6
                                       //tha vrisketai sti thesi x = 4 y=0 ara pos = 4
            buffer[pos] = value; //i kainourgia timi tha apothikeutei stin thesi 4 tou buffer tipou Color
        }
    }

    void Image::setData(const Color*& data_ptr) //xrisimeuei opote thelei na allaksw ola ta dedomena tis eikonas
    {
        if (buffer == NULL) { //ama einai adeios perase ta xaraktiristika tis eikonas ppm
            buffer = new imaging::Color[width * height];
        }
        for (int i = 0; i < width * height; i++) {
                buffer[i] = data_ptr[i];
            }//alliws opws parakatw me tin entoli memcpy:

        //memcpy(buffer, data_ptr, width * height * sizeof(Color));
        //i leitourgeia memcpy xrisimopoieitai gia tin antigrafi enos mplok dedomenwn apo mia dieuthinsi

        // proeleusis se mia dieuithinsi proorismou.i idea einai oti apla metaferw-antigrafw ta dedomena
        //ena pros ena ta dedomena ston proorismo.diladi edw antigrafw
        //ta dedomena tou data_ptr ston buffer mou gia megethos width*height*sizeofColor




    }
    //default: zero dimensions, nullptr for the buffer.
    //constructor
    Image::Image() : width(0), height(0), buffer(NULL) {}
    //constructor
    Image::Image(unsigned int width, unsigned int height) : width(width), height(height), buffer(NULL)
    {
    }
    //constructor
    Image::Image(unsigned int width, unsigned int height, const Color* data_ptr)
    {
        Image(width, height);
        setData(data_ptr); //metaferw ta dedomena tou data_ptr sto buffer mou
    }

    Image::Image(const Image& src) //dimiourgw ena image me vasi ta stoixeia enos allou antikeimenou Image
    {
        width = src.width;
        height = src.height;
        buffer = new Color[width * height];
        
        memcpy(buffer, src.buffer, width * height * sizeof(Color)); //src. buffer einai o buffer pou edwsa
    }
    //katastrofeas
    Image::~Image()
    {
        if (buffer)
            delete[] buffer;
    }

    Image& Image::operator=(const Image& right) //kaleitai otan idi s'ena arxikopoiimeno antikeimeno exei ekxwrithei mia timi apo allo idi iparxon
    {    //have the same elements one by one -self assignment
        if (this == &right) {
            return *this;
        }
       //deallovate memory
        if (buffer != NULL) {
            delete[] buffer;
        }

        width = right.width;
        height = right.height;
        //diethese kainourgio xwro
        buffer = new Color[width * height];
        //antegrapse ta stoixeia
        memcpy(buffer, right.buffer, width * height * sizeof(Color));

        return *this; //i alliws *this = right
    }
    //diavase ta periexomena enos antikeimenou apo to file
    bool Image::load(const std::string& filename, const std::string& format)
    {


        std::string nameCopy = filename.substr(filename.size() - 3,3); //apothikeuse stin metevliti nameCopy ta tria teleutaia grammata dil to ppm
        nameCopy.c_str(); //valta se pinaka charactirwn
        format.c_str(); //to idio kai gia to format
        for (int i = 0; i <3; i++){
           tolower(nameCopy[i]); //kanta mikra se periptwseis pou exw , Ppm PPm pPM pPM ktl
           tolower(format[i]);
        }


        if ( format == nameCopy) { //ouasiastika an format == 'ppm'
            int w;
            int h;
            float* ImageData = ReadPPM(filename.c_str(), &w, &h);
            if (ImageData == NULL) { //an dn edwse tipota
                std::cout << "Error reading ppm file" << std::endl;
                return false;
            }

            this->buffer = new Color[w * h];
            this->width = w;
            this->height = h;

            for (size_t i = 0, j = 0; i<(w)*(h)*3, j <(w)*(h); i+=3, j++){
                this->buffer[j].r = ImageData[i] ;
                this->buffer[j].g =  ImageData[i+1];
                this->buffer[j].b = ImageData[i+2];
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

      std::string nameCopy = filename.substr(filename.size() - 3,3); //apothikeuse stin metevliti nameCopy ta tria teleutaia grammata dil to ppm
      nameCopy.c_str(); //valta se pinaka charactirwn
      format.c_str(); //to idio kai gia to format
      for (int i = 0; i <3; i++){
         tolower(nameCopy[i]); //kanta mikra se periptwseis pou exw , Ppm PPm pPM pPM ktl
         tolower(format[i]);
      }
      if ( nameCopy == format ){
        if (this->buffer == NULL) {
            std::cout << "Cannot save null buffer" << std::endl;
            return false;
        }
        //einai 3 * width*height logw twn rgb pou einai 3 byte
        float* ImData = new float[3 * width * height];


        for (size_t i = 0, j = 0; i<(width)*(height)*3, j <(width)*(height); i+=3, j++){ // EDW EGINE 2/2 ALLAGH
            ImData[i] =this->buffer[j].r;
            ImData[i+1] =  this->buffer[j].g;
           ImData[i+2] =  this->buffer[j].b;
        }
        //i alliws
        //memcpy(ImData, this->buffer, width * height * sizeof(Color));
        return WritePPM(ImData, width, height, filename.c_str());
      }else{
        std::cout << "Not a ppm file!" << std::endl;
        return false;
      }
    }

} //namespace imaging
