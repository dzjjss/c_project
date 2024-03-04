#include "zombie.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "1. Zombie z1" << endl;
    Zombie z1;
    z1.setDestination(3, 4);
    z1.printInfo();

    cout << endl << "2. Zombie z2" << endl;
    Zombie* z2 = new Zombie(8, 8);
    z2->setDestination(5, 5);

    cout << endl << "3. Zombie z3" << endl;
    Zombie z3(22, 2, shotgun);
    z3.setFast(true);
    z3.setDestination(2, 2);

    // Update the positions one additional time
    z1.takeTurn();
    z2->takeTurn();
    z3.takeTurn();

    delete z2;
    return 0;
}