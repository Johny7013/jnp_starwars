#include<iostream>
#include<cassert>

#include "imperialfleet.h"
#include "rebelfleet.h"

using namespace std;

int main() {
	XWing<int> wing(10, 299796, 5);
    Explorer<int> exp(8, 2997960);
    TIEFighter<int> tf(20, 7);

    cout << wing.getShield() << endl;
    cout << exp.getShield() << endl;
    cout << tf.getShield() << endl;

    attack(tf, wing); //<TIEFighter, XWing>
    attack(tf, exp); //<TIEFighter, Explorer>

    cout<< wing.getAttackPower() << endl;

    cout << wing.getShield() << endl;
    cout << exp.getShield() << endl;
    cout << tf.getShield() << endl; 
}