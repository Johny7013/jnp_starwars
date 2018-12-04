#include "rebelfleet.h"
#include "imperialfleet.h"
#include "battle.h"
#include <cassert>
#include <iostream>

using namespace std;

int main() {

    // starwars_example
    XWing<float> xwing(100.0f, 300000.0f, 50.0f);
    Explorer<int> explorer(150, 400000);
    StarCruiser<unsigned> cruiser(1234, 100000, 11);
    DeathStar<long> deathStar(10000, 75);
    TIEFighter<unsigned> fighter(50, 9);
    ImperialDestroyer<int> destroyer(150, 20);
    auto battle = SpaceBattle<short, 1, 23,
            DeathStar<long>,
            Explorer<int>,
            TIEFighter<unsigned>,
            XWing<float>>(deathStar,
                          explorer,
                          fighter,
                          xwing);

    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 2);

    battle.tick(2);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(1);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(4);
    assert(battle.countRebelFleet() == 0);
    assert(battle.countImperialFleet() == 1);

    battle.tick(1); // Wypisuje "IMPERIUM WON\n".

    //starwars_example_end

    // time_test

    //static assert errors
    //auto battle_time1 = SpaceBattle<int, -1, 8>();
    //auto battle_time2 = SpaceBattle<int, 9, 8>();

    // require getCurrentTimeFunction
//    auto getCurrentTime(){
//        return currentTime;
//    }

//    auto battle_time = SpaceBattle<int, 4, 45>();
//
//    battle_time.tick(23);
//    assert(battle_time.getCurrentTime() == 27);
//
//    battle_time.tick(37);
//    assert(battle_time.getCurrentTime() == 18);
//
//    battle_time.tick(37);
//    assert(battle_time.getCurrentTime() == 9);
//
//    battle_time.tick(36);
//    assert(battle_time.getCurrentTime() == 45);
//
//    battle_time.tick(1);
//    assert(battle_time.getCurrentTime() == 0);

    //time_test_end


    // just_one_fraction

    // just rebelships
    auto battle_just_rebel = SpaceBattle<short, 2, 23,
            StarCruiser<unsigned>,
            Explorer<int>,
            XWing<float> >(cruiser, explorer, xwing);

    battle_just_rebel.tick(1); // "REBELLION WON\n"


    // just imperialships
    auto battle_just_imperial = SpaceBattle<short, 2, 23,
            DeathStar<long>,
            TIEFighter<unsigned>
            >(deathStar, fighter);

    battle_just_imperial.tick(1); // "IMPERIUM WON\n"


    // just_one_fraction_end

    // normal battles

    XWing<float> xwing21(35.0f, 300000.0f, 15.0f);
    XWing<float> xwing22(35.0f, 300000.0f, 15.0f);
    Explorer<long> explorer2(75, 400000);
    StarCruiser<unsigned> cruiser2(62, 100000, 41);
    DeathStar<long> deathStar2(90, 30);
    TIEFighter<unsigned> fighter21(15, 2);
    TIEFighter<long long> fighter22(15, 2);
    ImperialDestroyer<int> destroyer2(35, 10);
    auto battle2 = SpaceBattle<int, 6, 36,
            XWing<float>,
            XWing<float>,
            DeathStar<long>,
            Explorer<long>,
            TIEFighter<unsigned>,
            TIEFighter<long long>,
            ImperialDestroyer<int>,
            StarCruiser<unsigned>>(xwing21,
                          xwing22,
                          deathStar2,
                          explorer2,
                          fighter21,
                          fighter22,
                          destroyer2,
                          cruiser2);

    assert(battle2.countRebelFleet() == 4);
    assert(battle2.countImperialFleet() == 4);

    battle2.tick(3); //6
    assert(battle2.countRebelFleet() == 4);
    assert(battle2.countImperialFleet() == 4);

    battle2.tick(3); //9
    assert(battle2.countRebelFleet() == 2);
    assert(battle2.countImperialFleet() == 1);
    //status: 0 0 19 35 0 0 0 22

    battle2.tick(24); //12
    assert(battle2.countRebelFleet() == 2);
    assert(battle2.countImperialFleet() == 1);

    battle2.tick(1); //36
    assert(battle2.countRebelFleet() == 1);
    assert(battle2.countImperialFleet() == 0);
    //status: 0 0 0 5 0 0 0 0

    battle2.tick(1); // "REBELLION WON\n"


    XWing<unsigned long> xwing32(35, 300000, 15);
    XWing<float> xwing31(45.0f, 300000.0f, 10.0f);
    TIEFighter<double> fighter31(37, 20);
    TIEFighter<long long> fighter32(42, 7);

    auto battle3 = SpaceBattle<long long, 3, 10,
            TIEFighter<double>,
            XWing<unsigned long>,
            XWing<float>,
            TIEFighter<long long> >
                   (fighter31,
                    xwing32,
                    xwing31,
                    fighter32);

    assert(battle3.countRebelFleet() == 2);
    assert(battle3.countImperialFleet() == 2);

    battle3.tick(8); //3
    assert(battle3.countRebelFleet() == 2);
    assert(battle3.countImperialFleet() == 2);

    battle3.tick(1); //0
    assert(battle3.countRebelFleet() == 2);
    assert(battle3.countImperialFleet() == 2);
    // status: 12 8 18 17

    battle3.tick(8); //1
    assert(battle3.countRebelFleet() == 1);
    assert(battle3.countImperialFleet() == 1);
    // status: 0 0 11 7

    battle3.tick(1); //9
    assert(battle3.countRebelFleet() == 1);
    assert(battle3.countImperialFleet() == 0);
    // status: 0 0 4 0

    battle3.tick(0); // "REBELLION WON\n"

    // normal_battles_end
}
