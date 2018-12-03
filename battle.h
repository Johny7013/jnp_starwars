#ifndef BATTLE_H
#define BATTLE_H

#include <tuple>
#include <vector>
#include <iostream>
#include "imperialfleet.h"
#include "rebelfleet.h"

using namespace std;

enum Division {imperial, rebel};

template<typename T, T end, T cur = 0, T...results>
constexpr static auto squares() {
    if constexpr (cur * cur <= end)
        return squares<T, end, cur + 1, results..., cur * cur>();
    else
        return array<T, sizeof...(results)> ({results...});
}

template<typename R>
constexpr Division starshipFraction(){
    if constexpr (isRebelship<R>())
        return rebel;
    else if constexpr (isImperialship<R>())
        return imperial;
    else
        static_assert("An object that isn't a starship passed to battle.");
}

template<typename head, typename... tail>
constexpr static auto divisionIntoFractions() {
    if constexpr (sizeof...(tail) == 0)
        return tuple<int> (starshipFraction<head>());
    else
        return tuple_cat(tuple<int> (starshipFraction<head>()), divisionIntoFractions<tail...>());
}


template<typename T,T t0, T t1, typename... S>
class SpaceBattle {


    static_assert(t0 >= 0 && t0 <= t1, "t0 has wrong value");
    static_assert(t1 >= 0, "t1 has wrong value");
    

    T currentTime = t0;
    static constexpr auto battleTimes = squares<T, t1>();
    static constexpr auto division = divisionIntoFractions<S...>(); // 1 - rebel, 0 - imperial
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

            processFight<i + 1, j, size>();
        } else if constexpr (j < size){

            processFight<0, j + 1, size>();
        }
    }

    template<size_t i, size_t size>
    void setNumersOfShips(){
        if constexpr (i < size)
        {
            if(get<i>(division) == rebel)
                numberOfRebelianShips++;
            else
                numberOfImperialShips++;

            setNumersOfShips<i + 1, size>();
        }
    }

    // auxiliary function to print values of shields
    template<size_t i, size_t size>
    auto printShields(){
        if constexpr (i < size)
        {
            cout << get<i>(spaceships).getShield() << endl;
            printShields<i + 1, size>();
        }
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
    // after implementation of thick function make it private
    void fight(){
        processFight<0, 0, sizeof...(S)>();

        if(numberOfRebelianShips == 0 && numberOfImperialShips == 0)
            cout << "DRAW" << endl;
        else if(numberOfRebelianShips == 0)
            cout << "IMPERIUM WON" << endl;
        else if(numberOfImperialShips == 0)
            cout << "REBELLION WON" << endl;

        // print values
//        printShields<0, sizeof...(S)>();
//
//        cout << numberOfImperialShips << endl;
//        cout << numberOfRebelianShips << endl;
    }

    void tick(T timeStep) {
        size_t beg = 0;
        size_t end = battleTimes.size();

        while (beg + 1 < end) {
            size_t mid = (beg + end) / 2;

            if (battleTimes[mid] > currentTime)
                end = mid;
            else
                beg = mid;
        }

        if (battleTimes[beg] == currentTime || battleTimes[end] == currentTime)
            fight();

        currentTime += timeStep;
        // auto upper = upper_bound(battleTimes, battleTimes + battleTimes.size(), currentTime) - battleTimes;
        // if (upper >= 0 && upper < battleTimes.size() && currentTime = battleTimes[upper])
        //     fight();

        // currentTime += timeStep;
    }

};

#endif