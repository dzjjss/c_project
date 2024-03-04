#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_
#include <iostream>
#include <string>

using namespace std;

struct position
{
    int x;
    int y;
    position()
    {
        x = 0;
        y = 0;
    }
    position(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(const position& other) const
    {
        return (other.x == this->x && other.y == this->y);
    }

    bool operator!=(const position& other) const
    {
        return !(other.x == this->x && other.y == this->y);
    }

    string Info() { return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")"; }
};

typedef enum
{
    no      = 0,
    shotgun = 1,
    knife   = 2,
    rifle   = 3
} WeaponType;

class Weapon
{
protected:
    WeaponType wt;
    int        damage;   // 伤害
    int        range;    // 射程
public:
    WeaponType Type() { return wt; }
    Weapon();
    Weapon(int wt);
    ~Weapon();
    int Damage();
};


class Zombie
{
protected:
    bool     spoiled;       // if spoiled = true, zombie can't eat
    bool     Dead;          // Dead = true, zombie is dead
    bool     Fast;          // if Fast = true, zombie can run
    position Destination;   // the position of the destination
    position Current;       // the current position
    Weapon*  Wp;

public:
    Zombie();
    Zombie(int x, int y);
    Zombie(int x, int y, int wt);
    ~Zombie();
    position setDestination(int xPos, int yPos);

    inline int takeTurn()
{
    if (Destination == Current) {
        return 0;
    }

    int damage = 0;
    for (int i = 0; i < 3; ++i) {
        int diffx = Destination.x - Current.x;
        int diffy = Destination.y - Current.y;
        if (abs(diffx) > abs(diffy)) {
            if (diffx > 0) {
                Current.x += 1;
            }
            else {
                Current.x -= 1;
            }
        }
        else {
            if (diffy > 0) {
                Current.y += 1;
            }
            else {
                Current.y -= 1;
            }
        }

        if (Current == Destination) {
            break;
            // return this->Wp->Damage();
        }
    }

    if (this->Wp) {
        return this->Wp->Damage();
    }

    return 0;
}

    inline void printInfo()
{
    cout << "Current Position:" << Current.Info() << endl;
    cout << "Desitination Position:" << Destination.Info() << endl;
    if (this->Wp) {
        cout << "Weapon Type:" << this->Wp->Type() << endl;
    }
    else {
        cout << "Weapon Type: No Weapon" << endl;
    }

    return;
}

    inline void setFast(bool b)
{
    Fast = b;
}
    string hit()
    {
        if (Dead) {
            return "";
        }
        else {
            string hitMsg  = " Zombie hit!";
            string hitMsg2 = std::to_string(takeTurn()) + hitMsg;
            return hitMsg;
        }
    }
};

class Zombie28 : public Zombie
{
public:
    Zombie28();                       // Constructor
    Zombie28(int x, int y);           // Constructor
    Zombie28(int x, int y, int wt);   // Constructor
    ~Zombie28();                      // Destructor
    int  takeTurn();                  // Override takeTurn function
    void printInfo();                 // Override printInfo function
    void setFast(bool b);             // Override setFast function
};

#endif