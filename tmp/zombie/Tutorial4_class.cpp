#include "zombie.h"
#include <iostream>
using namespace std;

// to do
// 创建僵尸类
// 创建武器类
// 修改僵尸类
// 测试僵尸类和武器类

struct position
{
    int x;
    int y;
};

typedef enum
{
    shotgun = 1,
    knife   = 2,
    rifle   = 3
} weapon;

class Zombie
{
protected:
    bool     spoiled;       // 腐烂影响进食（if spoiled = true, zombie can't eat）
    bool     Dead;          // 死亡状态(Dead = true, zombie is dead)
    bool     Fast;          // 移动速度(if Fast = true, zombie can run)
    position Destination;   // 目的地
    position Current;       // 当前位置
public:
    position setDestination(int xPos, int yPos)
    {
        Destination.x = xPos;
        Destination.y = yPos;
        return Destination;
    }
    int takeTurn()   // 返回僵尸造成的伤害
    {
        int damage;
        return damage;
    }
    void printInfo()   // 打印僵尸信息, 让速度属性保持独立，死亡的跑尸那还是跑尸
    {
        if (Fast) {
            cout << "Zombie speed: "
                 << "fast" << endl;
        }
        else {
            cout << "Zombie speed: "
                 << "slow" << endl;
        }
    }
    string hit()
    {
        if (Dead) {
            return 0;
        }
        else {
            string hitMsg = " Zombie hit!";
            string hitMsg = to_string(takeTurn()) + hitMsg;
            return hitMsg;
        }
    }
};

class Weapon
{
protected:
    int damage;   // 伤害
    int range;    // 射程
public:
private:
};

// for test
/*
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
}
*/