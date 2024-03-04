#include "test.h"

int main()
{
    // print info
    BITStudent s;
    s.setID(123);
    s.setName("John");
    cout << "ID: " << s.getID() << endl;
    cout << "Name: " << s.getName() << endl;
}