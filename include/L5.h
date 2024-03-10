#ifndef _L5_H
#define _L5_H

#include <iostream>
#include <string>

using namespace std;

class test
{
private:
    string name;
    int    id;

public:
    test();
    ~test();
    void printInfo()
    {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
    }
    string getName() const { return name; };
    void   setName(const string& newName) { name = newName; };
    int    getID() const { return id; };
    void   setID(int newID) { id = newID; };
};

#endif   // _L5_H
