//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_SQUARE_ARRAY_HPP
#define SIMPLEGAMES_SQUARE_ARRAY_HPP


template<typename T>
class SquareArray {

private:
    T* data = nullptr;
    int as  = 0;   // array size
    int res = 0;   // array resolution

public:
    enum RP {      // matrix representation for access by x and y coordinates
        NORMAL,    // as is
        REVERSED,  // rotated to 180 degrees
        R_LEFT,    // rotated left
        R_RIGHT    // rotated right
    };
    SquareArray() = default;
    ~SquareArray() {delete[] data;}
    bool expand(const int& resolution);
    int size() {return as;}
    T* begin() {return data;}
    T* end() {return data + as;}
    T& at(const int& index) {return *(data + index);}
    T& at(const int& x, const int& y, RP repr = NORMAL);
};

template<typename T>
bool SquareArray<T>::expand(const int& resolution) {
    res = resolution;
    as = res * res;
    data = new T[as];
    if (data) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
T& SquareArray<T>::at(const int& x, const int& y, SquareArray::RP repr) {
    int offset = 0;
    switch (repr) {
        case NORMAL:   offset = x + y * res;                         break;
        case REVERSED: offset = (res - 1 - x) + (res - 1 - y) * res; break;
        case R_LEFT:   offset = x * res + (res - 1 - y);             break;
        case R_RIGHT:  offset = (res - 1 - x) * res + y;             break;
    }
    return *(data + offset);
}


#endif //SIMPLEGAMES_SQUARE_ARRAY_HPP
