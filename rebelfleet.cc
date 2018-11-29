#include<iostream>
#include<cassert>
using namespace std;

constexpr int MIN_STARCRUISER_SPEED = 99999;
constexpr int MAX_STARCRUISER_SPEED = 299795;
constexpr int MIN_XWING_EXPLORER_SPEED = 299796;
constexpr int MAX_XWING_EXPLORER_SPEED = 2997960;

enum SpaceshipType {explorer, starCruiser, xWing};

template<typename U, SpaceshipType spaceshipType, int minSpeed, int maxSpeed>
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

    template <SpaceshipType A = spaceshipType, typename = typename std::enable_if<spaceshipType != explorer>::type>
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

int main() {
    XWing<int> xwing(10, 299796, 5);
    int pow = xwing.getAttackPower();

    cout << pow << endl;

    xwing.takeDamage(3);

    int sh = xwing.getShield();

    cout << sh << endl;

    // Explorer<int> explorer(2, 3);
    // int pow2 = explorer.getAttackPower();
}