#include "zombie.h"

Weapon::Weapon()
{
    this->wt = no;
}

Weapon::Weapon(int wt)
{
    cout << "constructor: weapon(int)" << endl;
    this->wt = (WeaponType)wt;
}
Weapon::~Weapon()
{
    cout << "destructor: ~weapon()" << endl;
}

int Weapon::Damage()
{
    switch (wt) {
    case shotgun: return 3;
    case knife: return 2;
    case rifle: return 1;
    }

    return 0;
}

Zombie::Zombie()
{
    Current.x = 0;
    Current.y = 0;
    Fast      = false;
    Wp        = NULL;
    cout << "constructor: zombie() " << endl;
}

Zombie::Zombie(int x, int y)
{
    Fast      = false;
    Current.x = x;
    Current.y = y;
    Wp        = NULL;
    cout << "constructor: zombie(int, int) " << endl;
}

Zombie::Zombie(int x, int y, int wt)
{
    this->Wp  = new Weapon(wt);
    Fast      = false;
    Current.x = x;
    Current.y = y;
    cout << "constructor: zombie(int, int, int)" << endl;
}

Zombie::~Zombie()
{
    cout << "destructor: ~zombie()" << endl;
    if (Wp) {
        delete Wp;
    }
}

position Zombie::setDestination(int xPos, int yPos)
{
    Destination.x = xPos;
    Destination.y = yPos;
    if (this->Current != this->Destination) {
        cout << "The zombie is now at position(" << Current.x << "," << Current.y << ") "
             << "going to (" << Destination.x << "," << Destination.y << ")" << endl
             << endl;
    }
    else {
        cout << "The zombie is in the destination (" << Destination.x << ", " << Destination.y
             << ")" << endl
             << endl;
    }
    return Destination;
}