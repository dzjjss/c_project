#pragma once
#include <string>


using namespace std;

/**
* Given (to hopefully make your job easier).  These are simple structs to store data rather than
passing around a crazy number of variables.
* Your job is to make Shape2400 child classes.  Notice Shape2400 has PRIVATE member variables for
the shape bound and the colour plus:
* 1) A constructor
* 2) getter and setter methods for all member variables
* 3) a function isIntersectPoint that takes a point as an input and returns true if and only if that
point is intersecting the shape.
*    In this case, intersecting the generic shape means the point is in the bound
* 4) a function toString which takes no parameters and returns a string (text) message regarding the
shape like
*    "Shape2400 has bounds 0, 0, 100, 200 and is RGB colour (255, 255, 0)"
*
* Reminder: You will then need to make other child shapes and overload specific functions.
*  **Do not just copy and paste the shape code.**  These must be child classes. You will get 0
points for just copying and pasting provided code.
* Your child classes might require a new constructor or destructor, not getter and setter methods,
perhaps a new isIntersectPoint
* and a new version of toString
*/
#define BYTE unsigned char
struct RGB
{
    BYTE red;
    BYTE green;
    BYTE blue;
};

// A rectangular bounding region where the shape is located.
struct BOUND
{
    unsigned int xPos;
    unsigned int yPos;
    unsigned int width;
    unsigned int height;
};


struct POINT
{
    unsigned int xPos;
    unsigned int yPos;
};



class Shape2400
{
public:
    Shape2400();
    Shape2400(BOUND newBound, RGB newColour);
    void setBound(BOUND bnd);
    void setColour(RGB rgb);

    BOUND getBound();
    RGB   getColour();

    // TODO: For each child class, define these functions when needed
    // For example getArea of a circle would be the the circle radius * radius * pi
    virtual bool   isIntersectPoint(POINT pt);
    virtual double getArea()  = 0;
    virtual string toString() = 0;

protected:
    // Functions you can use
    string getColourString();
    string getBoundString();

private:
    BOUND bound;
    RGB   colour;
};
//---------------------------------Rect2400---------------------------------
class Rect2400 : public Shape2400
{
public:
    Rect2400(BOUND newBound, RGB newColour)
        : Shape2400(newBound, newColour){};
    bool   isIntersectPoint(POINT pt);
    double getArea();
    string toString();
};
//---------------------------------Circle2400---------------------------------
class Circle2400 : public Shape2400
{
public:
    Circle2400(BOUND newBound, RGB newColour);
    bool   isIntersectPoint(POINT pt);
    double getArea();
    string toString();

    double getRadius() const { return radius; }
    POINT  getCentre() const { return centre; }

private:
    double radius;
    POINT  centre;
};
//---------------------------------multiangle2400---------------------------------
//  class MultiAngle2400 : public Shape2400
//  {
//  public:
//      MultiAngle2400(BOUND newBound, RGB newColour)
//          : Shape2400(newBound, newColour){};
//      bool   isIntersectPoint(POINT pt);
//      double getArea(int n);
//      string toString();
//  };
