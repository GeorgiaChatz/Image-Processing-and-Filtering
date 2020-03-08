#ifndef _ARRAY
#define _ARRAY

#include <cstddef>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
namespace math {

    template <typename T>
    class Array {

    protected:
        unsigned int width, height;
        std::vector<T> buffer;

    public:
        unsigned int getWidth() const { return width; } // returns the width of the image
        unsigned int getHeight() const { return height; } // returns the height of the image

        T* getRawDataPtr();

        T getValue(unsigned int x, unsigned int y) const;

        void setValue(unsigned int x, unsigned int y, T& value);

        void setData(const T*& data_ptr);

        //constructor
        Array();

        Array(unsigned int width, unsigned int height);

        Array(unsigned int width, unsigned int height, const T* data_ptr);

        Array(const Array<T>& src);

        ~Array();

        Array<T>& operator=(const Array<T>& right);

        T& operator()(int x, int y);
    };

    /////////////////////////////////////////////TODO

    template <typename T>
    T* Array<T>::getRawDataPtr()
    {
        return buffer.data();
    }

    template <typename T>
    T Array<T>::getValue(unsigned int x, unsigned int y) const
    {
        if (x > width || y > height) {
            return T(0, 0, 0);
        }
        else {
            int pos = x + (y * width);
            return buffer[pos];
        }
    }

    template <typename T>
    void Array<T>::setValue(unsigned int x, unsigned int y, T& value)
    {
        if (x > width || y > height) {
            std::cout << "The cordinates are out of bounds" << std::endl;
            return;
        }
        else {
            int pos = x + (y * width);
            buffer[pos] = value;
        }
    }

    template <typename T>
    void Array<T>::setData(const T*& data_ptr)
    {
        if (buffer.size() == 0) {
            buffer.resize(width * height);
        }
        for (int i = 0; i < width * height; i++) {
            buffer[i] = data_ptr[i];
        }
    }

    template <typename T>
    Array<T>::Array() : width(0), height(0) { buffer.clear(); }

    template <typename T>
    Array<T>::Array(unsigned int width, unsigned int height) : width(width), height(height) { buffer.clear(); }

    template <typename T>
    Array<T>::Array(unsigned int width, unsigned int height, const T* data_ptr)
    {
        Array<T>(width, height);
        setData(data_ptr);
    }

    template <typename T>
    Array<T>::Array(const Array<T>& src)
    {
        width = src.width;
        height = src.height;
        buffer.resize(width * height);

        memcpy(buffer.data(), src.buffer.data(), width * height * sizeof(T));
    }

    template <typename T>
    Array<T>::~Array()
    {
        buffer.clear();
    }

    template <typename T>
    Array<T>& Array<T>::operator=(const Array<T>& right)
    {
        if (this == &right) {
            return *this;
        }
        //deallovate memory
        buffer.clear();

        width = right.width;
        height = right.height;
        //diethese kainourgio xwro
        buffer.resize(width * height);
        //antegrapse ta stoixeia
        memcpy(buffer.data(), right.buffer.data(), width * height * sizeof(T));

        return *this;
    }

    template <typename T>
    T& Array<T>::operator()(int x, int y)
    {
        if (x > width || y > height) {
            std::cerr << "Coordinates are out of bounds" << std::endl;
        }
        else {
            return buffer[x + y * width];
        }
    }

} // namespace math
#endif
