#include <list>

#include "imperialfleet.h"
#include "rebelfleet.h"

template <int I>
struct squared {
    squared<I - 1> rest;
    int x;
    squared() : x((I - 1) * (I - 1)) {}
    int operator[] (int i){
        return reinterpret_cast<int*>(this)[i];
    }
};

template <>
struct squared<1> {
    int x;
    squared() : x(0) {}
    int operator[] (int i){
        return reinterpret_cast<int*>(this)[i];
    }
};
