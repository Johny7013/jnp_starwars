#ifndef BATTLE_H
#define BATTLE_H

#include <tuple>
#include <vector>
#include <iostream>
#include "imperialfleet.h"
#include "rebelfleet.h"

using namespace std;

template <int I>
struct squared {
private:
    squared<I - 1> rest;
    int x;
public:
    squared() : x((I - 1) * (I - 1)) {}
    auto getNext(){
        return rest;
    }
    int getValue(){
        return x;
    }
    bool isLast(){
        return false;
    }

};

template <>
struct squared<1> {
private:
    int x;
public:
    squared() : x(0) {}
    int getValue(){
        return x;
    }
    bool isTrue(){
        return false;
    }
};

//constexpr countSqrt()



template<typename T,T t0, T t1, typename... S>
class SpaceBattle {
    T t = t0;
    squared<t1> squares; //to repair
    tuple<S...> spaceships;
    vector<int> rebelFleet, imerialFleet;
    void check(){
        static_assert(t0 >= 0 && t0 <= t1, "t0 has wrong value");
        static_assert(t1 >= 0, "t1 has wrong value");
    }

public:
    SpaceBattle(S... s): spaceships(make_tuple(s...)) {
        auto y = std::get<0>(spaceships);
        cout << y.getShield() << endl;
    }

};

#endif
