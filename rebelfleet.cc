 #include<iostream>
 #include<cassert>
 #include"imperialfleet.h"

 using namespace std;

// constexpr int MIN_STARCRUISER_SPEED = 99999;
// constexpr int MAX_STARCRUISER_SPEED = 299795;
// constexpr int MIN_XWING_EXPLORER_SPEED = 299796;
// constexpr int MAX_XWING_EXPLORER_SPEED = 2997960;

// template<typename U, bool canAttack, int minSpeed, int maxSpeed>
// class RebelStarship {
//     U shield;
//     U speed;
//     U attackPower;
//     constexpr static bool attackShip = canAttack;

//     template<typename I, typename R>
//     friend void attack(I &imperialShip, R &rebelShip);

// public:
//     using valueType = U;

//     template <bool A = canAttack, typename = std::enable_if_t<!A>>
//     RebelStarship(U shield, U speed): shield(shield), speed(speed) {
//         assert(speed <= maxSpeed && speed >= minSpeed);
//     }

//     template <bool A = canAttack, typename = std::enable_if_t<A>>
//     RebelStarship(U shield, U speed, U attackPower): shield(shield), speed(speed), attackPower(attackPower) {
//         assert(speed <= maxSpeed && speed >= minSpeed);
//     }

//     U getShield() {
//         return shield;
//     }

//     U getSpeed() {
//         return speed;
//     }

//     void takeDamage(U damage) {
//         shield = damage > shield ? 0 : shield - damage;
//     }

//     template <bool A = canAttack, typename = std::enable_if_t<A>>
//     U getAttackPower() {
//         return attackPower;
//     }
// };

// template<typename U>
// using XWing = RebelStarship<U, true, MIN_XWING_EXPLORER_SPEED, MIN_XWING_EXPLORER_SPEED>;

// template<typename U>
// using StarCruiser = RebelStarship<U, true, MIN_STARCRUISER_SPEED, MAX_STARCRUISER_SPEED>;

// template<typename U>
// using Explorer = RebelStarship<U, false, MIN_XWING_EXPLORER_SPEED, MAX_XWING_EXPLORER_SPEED>;

// template<typename>
// struct isRebelshipBase: false_type{};

// template<typename U, bool canAttack, int minSpeed, int maxSpeed>
// struct isRebelshipBase<RebelStarship<U, canAttack, minSpeed, maxSpeed>>: true_type{};


// template<typename R>
// bool isRebelship() {
//     return isRebelshipBase<R>::value;
// }

 int main() {
     XWing<int> xwing(10, 299796, 5);
     TIEFighter<int> tf(10, 10);
     // int pow = xwing.getAttackPower();

     cout << isRebelship<XWing<int>>() << endl;
     cout << isRebelship<TIEFighter<int>>() << endl;
     cout << isRebelshipBase<XWing<int>>::value<< endl;

     // Explorer<int> explorer(2, 3);
     // int pow2 = explorer.getAttackPower();
 }