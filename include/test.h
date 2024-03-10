#ifndef TEST_H
#define TEST_H

#include <string>
#include <vector>

using namespace std;

class student
{
private:
    struct instance
    {
        int    id;
        string name;
    };
    instance data;   // the instance to store the data
public:
    // getters
    int    getID() const { return data.id; };
    string getName() const { return data.name; }
    // setters
    void setID(int newID) { data.id = newID; };
    void setName(const string& newName) { data.name = newName; };
};

class Schedule
{
private:
    struct Event
    {
        string name;
        string date;
        string time;
    };
    vector<Event> events;
    int           count;

public:
    void  addEvent(Event e);
    Event getEvent() const { return events[count]; };
    void  setEvent(int index, Event e);
};

class BITStudent : public student
{
private:
    int      algID;
    Schedule schedule;
};

#endif   // TEST_H
