#ifndef _FILTER
#define _FILTER

#include "Array.h"
#include "Image.h"
#include "Vec3.h"
#include <iostream>

using namespace std;
using namespace math;
using namespace imaging;

class Filter {
public:
    virtual Image operator<<(const Image& image) = 0;

    Filter() {}

    Filter(const Filter& f) {}
};

#endif // _FILTER
