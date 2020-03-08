#include "Color.h"
#include "Image.h"
#include "ppm.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
using namespace imaging;
//dimiourgia arnitikou
//arnitiko = (1,1,1) - to pixel sti thesi (x,y)
Image getNegative(const Image& input)
{
    Image pic = input;

    for (int i = 0; i < pic.getWidth(); i++) {
        for (int j = 0; j < pic.getHeight(); j++) {
            Color c = pic.getPixel(i, j); //pare to kathe pixel
            Color new_col(1., 1., 1.);
            new_col = new_col - c; //ektelese ti sinartisi p(1,1,1)-p(x,y)
            pic.setPixel(i, j, new_col);//to epanatopothetw me to kainourgio xroma
        }
    }

    return pic;
}
int main(int argc , char * argv[]){

     string filename;
     if ( argv[1] != NULL){
       filename = argv[1];
     }else{
       cout << "File name of the Image to load: " << endl;
       cin >> filename;
     }

     fstream file(filename.c_str() , ios:: out | ios:: in | ios::binary);

     if ( !file.is_open()){
       cerr << "File could not be opened!" << endl;
     }


     Image img;
     if ( img.load(filename , "ppm")){
       cout << "Image dimensions are : " << img.getWidth() << " X " << img.getHeight() << endl;
       Image neg = getNegative(img);
       size_t pos = filename.find(".");
       string filename2 = filename;
       filename2.insert(pos  , "_neg" );
       neg.save(filename2 , "ppm");
       return 0;
     }
}
