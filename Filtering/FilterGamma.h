#ifndef _FILTER_GAMMA_
#define _FILTER_GAMMA_

#include "Filter.h"
#include <cmath>

namespace imaging {
    class FilterGamma {
    protected:
        double gamma;

    public:
        FilterGamma(double gamma) : gamma(gamma) {}

        Image operator<<(const Image& image) const
        {
            Image pic = image;
            for (int i = 0; i < pic.getWidth(); i++) {
                for (int j = 0; j < pic.getHeight(); j++) {
                    Color pxy = pic.getValue(i, j); //pare to kathe pixel
                    Color new_col;
                    new_col.x = pow(pxy.x, gamma);
                    new_col.y = pow(pxy.y, gamma);
                    new_col.z = pow(pxy.z, gamma);

                    pic.setValue(i, j, new_col);
                } //to epanatopothetw me to kainourgio xroma
            }
            return pic;
        }

        void set_gamma(double gamma) { gamma = gamma; }

        Color get_gamma() { return gamma; }
    };
} // namespace imaging

#endif
