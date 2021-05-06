#pragma once
#include <iostream>

template<typename T>
class MWindow {
public:
    T minX, maxX, minY, maxY;
    MWindow(T minX, T maxX, T minY, T maxY)
        : minX(minX), maxX(maxX), minY(minY), maxY(maxY) {}


    T Width() {
        return maxX - minX;
    }
   
    T Height() {
        return maxY - minY;
    }

    T Size() {
        return Height() * Width();
    }
    void Reset();
};