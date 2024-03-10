#include "Shape2400.h"
#include <cmath>
//#include <iostream> for debug, bug clangd will note that this is not used which is annoying

// Blank constructor for a shape
Shape2400::Shape2400()
{
    RGB   white = {255, 255, 255};
    BOUND bnd   = {0, 0, 0, 0};
    setBound(bnd);
    setColour(white);
}

// Constructor for a shape within parameters
Shape2400::Shape2400(BOUND newBound, RGB newColour)
{
    setBound(newBound);
    setColour(newColour);
}

// Set the bounding region of the shape
void Shape2400::setBound(BOUND bnd)
{
    bound = bnd;
}

// Set the colour of the shape
void Shape2400::setColour(RGB rgb)
{
    colour = rgb;
}

// Returns the bounding region of the shape.
BOUND Shape2400::getBound()
{
    return this->bound;
}

// Return the fill colour of the shape.
RGB Shape2400::getColour()
{
    return this->colour;
}

/*
 Determines if point pt is inside the shape. For a generic shape, that means the point is in the
 rectangular bound region. Return true if pt is in the shape and false otherwise.
*/
bool Shape2400::isIntersectPoint(POINT pt)
{
    bool intersect = pt.xPos >= this->bound.xPos && pt.xPos < this->bound.xPos + bound.width &&
                     pt.yPos >= this->bound.yPos && pt.yPos < this->bound.yPos + bound.height;
    return intersect;
}

// Get a string representation of the shape's bound region.
string Shape2400::getBoundString()
{
    BOUND  bound     = getBound();
    string boundText = "(x:" + to_string(bound.xPos);
    boundText        = boundText + ", y:" + to_string(bound.yPos) + ")\n";
    boundText        = boundText + "width and height: (w:" + to_string(bound.width) +
                ", h:" + to_string(bound.height) + ")";
    return boundText;
}

// Get a string representation of the shape's colour
string Shape2400::getColourString()
{
    RGB    colour     = this->getColour();
    string colourText = "RGB Colour: (R:" + to_string(colour.red) +
                        ", G:" + to_string(colour.green) + ", B:" + to_string(colour.blue) + ")";
    return colourText;
}


double Shape2400::getArea()
{
    return (double)bound.width * bound.height;
}


// Create a string describing the shape such as the bounding region and colour.
string Shape2400::toString()
{
    BOUND bound = getBound();

    string boundText  = getBoundString();
    string colourText = getColourString();
    string shapeTxt =
        "Shape (area:" + to_string(getArea()) + ") at location " + boundText + " " + colourText;
    return shapeTxt;
}
//------------------------------------Rect2400------------------------------------
bool Rect2400::isIntersectPoint(POINT pt)
{
    BOUND b         = getBound();
    bool  intersect = pt.xPos >= b.xPos && pt.xPos < b.xPos + b.width && pt.yPos >= b.yPos &&
                     pt.yPos < b.yPos + b.height;
    return intersect;
}
double Rect2400::getArea()
{
    BOUND b = getBound();
    return (double)b.width * b.height;
};
string Rect2400::toString()
{
    return getBoundString() + "\n" + getColourString();
};

//------------------------------------Circle2400------------------------------------
Circle2400::Circle2400(BOUND newBound, RGB newColour)
    : Shape2400(newBound, newColour)
{
    // The obtained point is the lower-left vertex of the circumscribed square of the circle, and
    // the diameter is the minimum of the width or height.
    this->radius = newBound.width / 2.0f;
    // or this->radius = newBound.height / 2.0f;
    this->centre = {newBound.xPos + (int)radius, newBound.yPos + (int)radius};
};
bool Circle2400::isIntersectPoint(POINT pt)
{
    double radius   = getRadius();
    POINT  centre   = getCentre();
    double a        = (double)pt.xPos - centre.xPos;
    double b        = (double)pt.yPos - centre.yPos;
    double distance = sqrt(pow(a, 2) + pow(b, 2));

    // For debug, all right, we need int rather unsigned int to stock a and b
    // And we neet to convert a and b to double to use pow, otherwise it will be an error
    // cout << "Xdis: " << a << ", Ydis: " << b << endl;
    // cout << "Centre: (" << centre.xPos << ", " << centre.yPos << ") ";
    // cout << "Radius: " << radius << ", Distance: " << distance << endl;

    bool intersect = radius >= distance;
    return intersect;
};
double Circle2400::getArea()
{
    BOUND  b      = getBound();
    double radius = getRadius();
    return M_PI * this->radius * this->radius;
};
string Circle2400::toString()
{
    return getBoundString() + "\n" + getColourString();
};
//------------------------------------multiangle2400------------------------------------
/*
bool MultiAngle2400::isIntersectPoint(POINT pt)
{
    BOUND b         = getBound();
    bool  intersect = pt.xPos >= b.xPos && pt.xPos < b.xPos + b.width && pt.yPos >= b.yPos &&
                     pt.yPos < b.yPos + b.height;
    return intersect;
};
double MultiAngle2400::getArea(int n)
{
    BOUND b = getBound();
};
*/
