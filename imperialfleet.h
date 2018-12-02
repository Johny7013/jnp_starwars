#ifndef IMPERIALFLEET_H
#define IMPERIALFLEET_H

#include<iostream>
#include<cassert>
#include"rebelfleet.h"

using namespace std;

enum ImperialSpaceshipType {deathStar, imperialDestroyer, tieFighter};

template<typename U, ImperialSpaceshipType>
class ImperialStarship {
	U shield;
	U attackPower;
public:
	using valueType = U;

	ImperialStarship(U shield, U attackPower): shield(shield), attackPower(attackPower) {}

	U getShield() {
        return shield;
    }

    U getAttackPower() {
        return attackPower;
    }

    void takeDamage(U damage) {
        shield = damage > shield ? 0 : shield - damage;
    }
};

template<typename U>
using DeathStar = ImperialStarship<U, deathStar>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U, imperialDestroyer>;

template<typename U>
using TIEFighter = ImperialStarship<U, tieFighter>;

template<typename I, typename R>
void attack(I &imperialShip, R &rebelShip) {
	rebelShip.takeDamage(imperialShip.getAttackPower());
	if constexpr (R::attackShip)
		imperialShip.takeDamage(rebelShip.getAttackPower());
}

template<typename>
struct isImperialshipBase: false_type{};

template<typename U, ImperialSpaceshipType imperialShip>
struct isImperialshipBase<ImperialStarship<U, imperialShip>>: true_type{};


template<typename R>
bool isImperialship() {
    return isImperialshipBase<R>::value;
}

#endif