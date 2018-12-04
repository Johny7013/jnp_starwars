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

    //get tests
    assert(xwing.getShield() == 100);
    assert(xwing.getSpeed() == 300000);
    assert(xwing.getAttackPower() == 50);
    //assert(explorer.getAttackPower() == 23); //expected error
    assert(fighter.getAttackPower() == 9);
    assert(fighter.getShield() == 50);

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

    cout << "Starwars example correct answer: " << "IMPERIUM WON" << endl;

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

    cout << endl << "Just rebelships correct answer: " << "REBELLION WON" << endl;

    battle_just_rebel.tick(1); // "REBELLION WON\n"


    // just imperialships
    auto battle_just_imperial = SpaceBattle<short, 2, 23,
            DeathStar<long>,
            TIEFighter<unsigned>
            >(deathStar, fighter);

    cout << endl << "Just imperialships correct answer: " << "IMPERIUM WON" << endl;

    battle_just_imperial.tick(1); // "IMPERIUM WON\n"


    // just_one_fraction_end

    // empty_battle

    auto battle_empty = SpaceBattle<int, 4, 45>();

    cout << endl << "Empty battle correct answer: " << "DRAW" << endl;

    battle_empty.tick(1000000); // "DRAW\n"

    // empty_battle_end

    // normal battles

    //battle2
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

    cout << endl << "Battle2 correct answer: " << "REBELLION WON" << endl;

    battle2.tick(1); // "REBELLION WON\n"

    // battle3
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

    cout << endl << "Battle3 correct answer: " << "REBELLION WON" << endl;

    battle3.tick(0); // "REBELLION WON\n"

    //battle4
    StarCruiser<unsigned> cruiser4(123, 100000, 80);
    DeathStar<long> deathStar4(100, 75);
    // starship with shield = 0
    XWing<int> xwing41(0, 2997960, 3);
    // starship with shield = -1
    XWing<int> xwing42(-1, 299796, 3);

    auto battle4 = SpaceBattle<int, 2, 4,
            StarCruiser<unsigned>,
            DeathStar<long>,
            XWing<int>,
            XWing<int>>
            (cruiser4,
             deathStar4,
             xwing41,
             xwing42);

    battle4.tick(2); //2
    assert(battle4.countRebelFleet() == 1);
    assert(battle4.countImperialFleet() == 1);

    battle4.tick(2); //4
    assert(battle4.countRebelFleet() == 1);
    assert(battle4.countImperialFleet() == 1);

    battle4.tick(2); //1
    assert(battle4.countRebelFleet() == 0);
    assert(battle4.countImperialFleet() == 0);

    cout << endl << "Battle4 correct answer: " << "DRAW" << endl;
    battle4.tick(0); // "DRAW\n"

    // normal_battles_end

    // const starships
    const StarCruiser<unsigned> cruiser_const(123, 100000, 80);
    const DeathStar<long> deathStar_const(100, 75);
    const Explorer<int> explorer_const(150, 400000);

    // get tests
    assert(cruiser_const.getShield() == 123);
    assert(cruiser_const.getAttackPower() == 80);
    assert(cruiser_const.getSpeed() == 100000);
    assert(deathStar_const.getAttackPower() == 75);
    assert(deathStar_const.getShield() == 100);
    assert(explorer_const.getSpeed() == 400000);
    assert(explorer_const.getShield() == 150);
    //assert(explorer_const.getAttackPower() == 3); //expected error


    // compliation errors on const starships
    // can't create battle with const starships (generally it makes no sense)
//    auto battle_const = SpaceBattle<int, 2, 4,
//            const StarCruiser<unsigned>,
//            const DeathStar<long>>
//            (cruiser_const,
//             deathStar_const);

    //deathStar_const.takeDamage(3);

    //attack(deathStar_const, cruiser_const);

    // const_strarships_end

    // const SpaceBattle

    const SpaceBattle battle6 = SpaceBattle<int, 2, 4,
            StarCruiser<unsigned>,
            DeathStar<long>,
            XWing<int>,
            XWing<int>>
            (cruiser4,
             deathStar4,
             xwing41,
             xwing42);

    assert(battle6.countRebelFleet() == 1);
    assert(battle6.countImperialFleet() == 1);
}
