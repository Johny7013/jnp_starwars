#ifndef REBELFLEET_H
#define REBELFLEET_H

#include<iostream>
#include<cassert>

using namespace std;

constexpr int MIN_STARCRUISER_SPEED = 99999;
constexpr int MAX_STARCRUISER_SPEED = 299795;
constexpr int MIN_XWING_EXPLORER_SPEED = 299796;
constexpr int MAX_XWING_EXPLORER_SPEED = 2997960;

enum RebelSpaceshipType {explorer, starCruiser, xWing};

template<typename U, RebelSpaceshipType spaceshipType, int minSpeed, int maxSpeed>
class RebelStarship {
    U shield;
    U speed;
    U attackPower;
public:
    using valueType = U;

    RebelStarship(U shield, U speed): shield(shield), speed(speed) {
        assert(speed <= maxSpeed && speed >= minSpeed);
    }

    RebelStarship(U shield, U speed, U attackPower): shield(shield), speed(speed), attackPower(attackPower) {
        assert(speed <= maxSpeed && speed >= minSpeed);
    }

    U getShield() {
        return shield;
    }

    U getSpeed() {
        return speed;
    }

    void takeDamage(U damage) {
        shield = damage > shield ? 0 : shield - damage;
    }

    bool canAttack() {
        return spaceshipType != explorer;
    }

    template <RebelSpaceshipType A = spaceshipType, typename = typename std::enable_if<spaceshipType != explorer>>
    U getAttackPower() {
        return attackPower;
    }
};

template<typename U>
using XWing = RebelStarship<U, xWing, MIN_XWING_EXPLORER_SPEED, MIN_XWING_EXPLORER_SPEED>;

template<typename U>
using StarCruiser = RebelStarship<U, starCruiser, MIN_STARCRUISER_SPEED, MAX_STARCRUISER_SPEED>;

template<typename U>
using Explorer = RebelStarship<U, explorer, MIN_XWING_EXPLORER_SPEED, MAX_XWING_EXPLORER_SPEED>;


#endif