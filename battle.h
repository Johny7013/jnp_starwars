#ifndef BATTLE_H
#define BATTLE_H

#include <tuple>
#include <vector>
#include <iostream>
#include "imperialfleet.h"
#include "rebelfleet.h"

using namespace std;

enum Fraction {imperial, rebel};

template<typename T, T end, T cur = 0, T...results>
constexpr static auto squares() {
    if constexpr (cur * cur <= end)
        return squares<T, end, cur + 1, results..., cur * cur>();
    else
        return array<T, sizeof...(results)> ({results...});
}


template<typename R>
constexpr Fraction starshipFraction(){
    static_assert(isRebelship<R>() || isImperialship<R>(),
            "An object that isn't a  non-const starship passed to battle.");

    if constexpr (isRebelship<R>())
        return rebel;
    else
        return imperial;
}

template<typename Starship, typename... Ships>
constexpr static auto divideShipsIntoFractions() {
    if constexpr (sizeof...(Ships) == 0)
        return tuple<int> (starshipFraction<Starship>());
    else
        return tuple_cat(tuple<int> (starshipFraction<Starship>()), divideShipsIntoFractions<Ships...>());
}

template<typename... Ships>
constexpr static auto divisionIntoFractions(){
    if constexpr (sizeof... (Ships) == 0)
        return tuple<> ();
    else
        return divideShipsIntoFractions<Ships...>();
}


template<typename T,T t0, T t1, typename... S>
class SpaceBattle {

    static_assert(t0 >= 0 && t0 <= t1, "t0 has wrong value");
    static_assert(t1 >= 0, "t1 has wrong value");

    T currentTime = t0;
    static constexpr auto battleTimes = squares<T, t1>();
    static constexpr auto division = divisionIntoFractions<S...>();
    tuple<S...> spaceships;
    size_t numberOfImperialShips = 0;
    size_t numberOfRebelianShips = 0;

    template<typename W>
    bool isAlive (W starship) {
        return starship.getShield() > 0;
    }

    template<size_t i, size_t j, size_t size>
    void processFight(){
        if constexpr (i < size && j < size){

            if constexpr (get<i>(division) == imperial && get<j>(division) == rebel) {

                if(isAlive(get<i>(spaceships)) && isAlive(get<j>(spaceships))){
                    attack(get<i>(spaceships), get<j>(spaceships));

                    if(!isAlive(get<i>(spaceships)))
                        numberOfImperialShips--;
                    if(!isAlive(get<j>(spaceships)))
                        numberOfRebelianShips--;
                }
            }

            if constexpr (get<i>(division) == imperial)
                processFight<i, j + 1, size>();
            else
                processFight<i + 1, 0, size>();

        } else if constexpr (i < size){

            processFight<i + 1, 0, size>();
        }
    }

    template<size_t i, size_t size>
    void setNumersOfShips(){
        if constexpr (i < size)
        {
            if(get<i>(division) == rebel && isAlive(get<i>(spaceships)))
                numberOfRebelianShips++;
            else if(get<i>(division) == imperial && isAlive(get<i>(spaceships)))
                numberOfImperialShips++;

            setNumersOfShips<i + 1, size>();
        }
    }

    void fight(){
        processFight<0, 0, sizeof...(S)>();
    }


public:

    SpaceBattle(S... s): spaceships(make_tuple(s...)) {
        setNumersOfShips<0, sizeof...(S)>();
    }
    size_t countImperialFleet(){
        return numberOfImperialShips;
    }
    size_t countRebelFleet(){
        return numberOfRebelianShips;
    }

    void tick(T timeStep) {

        if(numberOfRebelianShips == 0 && numberOfImperialShips == 0)
            cout << "DRAW\n";
        else if(numberOfRebelianShips == 0)
            cout << "IMPERIUM WON\n";
        else if(numberOfImperialShips == 0)
            cout << "REBELLION WON\n";
        else{
            // binary search to check if the currentTime is a square
            size_t beg = 0;
            size_t end = battleTimes.size() - 1;
            size_t mid;

            while (beg + 1 < end) {
                mid = (beg + end) / 2;

                if (battleTimes[mid] > currentTime)
                    end = mid;
                else
                    beg = mid;
            }

            if (battleTimes[beg] == currentTime || battleTimes[end] == currentTime)
                fight();
        }

        currentTime = (currentTime + timeStep) % (t1 + 1);
    }
};

#endif