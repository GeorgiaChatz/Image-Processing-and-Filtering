#include "Array.h"
#include "Filter.h"
#include "FilterGamma.h"
#include "FilterLinear.h"
#include "Image.h"
#include "Vec3.h"
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
#include <typeinfo>
#include <vector>
using namespace std;
using namespace imaging;
using namespace math;

int main(int argc, char* argv[])
{

    Image img;
    string filename = argv[argc - 1]; //to teleutaio stoixeio tha nai panta to onoma tis eikonas
    if (img.load(filename, "ppm")) {
        int i = 1;
        string filterName;
        if (strcmp(argv[i], "-f") == 0) { //strcmp->compare two strings ,if ==0 means they have the same value
            while (i < argc - 1) {
                i++;
                filterName = argv[i];
                if (filterName != "gamma" && filterName != "linear") { //lathos to onoma filtrou i den exei valei filtro px filter -f Image02.ppm na termatizei
                    cerr << "Wrong definition or name of filter or no filter " << endl;
                    return 0;
                }

                if (filterName == "gamma") {
                    i++;
                    double gamma = atof(argv[i]); //atof -> metatrepei to string se double
                    if (!(gamma > 2.0 || gamma < 0.5)) { //elegxos oriwn gia to gamma
                        FilterGamma f(gamma); //antikeimeno FilterGamma
                        img = f << img; //eikona me to  filtro
                        i++;
                    }
                    else {
                        cout << "Gamma out of bounds" << endl;
                        return 0;
                    }
                }
                if (filterName == "linear") {
                    math::Vec3<float> col1(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
                    math::Vec3<float> col2(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
                    FilterLinear f(col1, col2); //antikeimeno FilterLinear
                    img = f << img;
                    i += 7;
                }
            }
        }
        else {
            cerr << "Error , you must type -f before filter  " << endl; //an einai px filter gamma 2.0 Image02.ppm xoris to -f
            return 0;
        }

        string filename2 = filename;
        filename2.insert(0, "filtered_");
        img.save(filename2, "ppm"); //apothikeuse tin eikona me to filtro
        return 0;
    }
}
