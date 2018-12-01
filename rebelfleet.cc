#include<iostream>
#include<cassert>

#include "rebelfleet.h"

using namespace std;

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