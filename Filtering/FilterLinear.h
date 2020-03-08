#ifndef _FILTER_LINEAR_
#define _FILTER_LINEAR_

#include "Filter.h"

namespace imaging {
    typedef math::Vec3<float> Color;
    class FilterLinear {
    protected:
        Color a, c;

    public:
        FilterLinear(Color a, Color c) : a(a), c(c) {}
        Image operator<<(const Image& image) const
        {
            Image pic = image;
            for (int i = 0; i < pic.getWidth(); i++) {
                for (int j = 0; j < pic.getHeight(); j++) {
                    Color pxy = pic.getValue(i, j);
                    Color new_col;
                    new_col = pxy * a + c; //p'(x,y) = a*p(x,y) + c
                    //PERIORISMOS ORIWN
                    if (new_col.x > 1.) {
                        new_col.x = 1;
                    }

                    if (new_col.y > 1.) {
                        new_col.y = 1;
                    }

                    if (new_col.z > 1.) {
                        new_col.z = 1;
                    }

                    if (new_col.x < 0.) {
                        new_col.x = 0;
                    }

                    if (new_col.y < 0.) {
                        new_col.y = 0;
                    }

                    if (new_col.z < 0.) {
                        new_col.z = 0;
                    }

                    pic.setValue(i, j, new_col);
                }
            }
            return pic;
        }
    };
} // namespace imaging

#endif
