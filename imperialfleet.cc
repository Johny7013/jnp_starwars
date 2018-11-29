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
void attack(I imperialShip, R rebelShip) {
	rebelShip.takeDamage(imperialShip.getAttackPower());
	if (rebelShip.canAttack())
		imperialShip.takeDamage(rebelShip.getAttackPower());
}


int main() {
	XWing<int> wing(10, 299796, 5);
    Explorer<int> exp(8, 2997960);
    TIEFighter<int> tf(20, 7);

    cout << wing.getShield() << endl;
    cout << exp.getShield() << endl;
    cout << tf.getShield() << endl;

    attack<TIEFighter, XWing>(tf, wing);
    attack<TIEFighter, Explorer>(tf, exp);

    cout<< wing.getAttackPower() << endl;

    cout << wing.getShield() << endl;
    cout << exp.getShield() << endl;
    cout << tf.getShield() << endl; 
}