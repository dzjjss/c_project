#include "Shape2400.h"
#include <iostream>
// Suyuan Chen

using namespace std;

int main()
{
    // GIVEN to hopefully make your jobs easier.
    // Make a bunch of DIFFERENT shapes
    // Print out the info
    // BOUND:{x, y, w, h}
    Rect2400 rect1({10, 20, 50, 25}, {(BYTE)255, '\0', '\0'});
    Rect2400 rect2({60, 45, 50, 25}, {(BYTE)255, (BYTE)100, '\0'});
    // A circle will have the diameter equalto the minimum of the bound’s width or height.
    Circle2400  circle1({50, 50, 20, 10}, {'\0', (BYTE)255, '\0'});
    Circle2400  circle2({60, 60, 20, 30}, {'\0', (BYTE)255, (BYTE)100});
    Polygon2400 poly1(
        {0, 0, 0, 0}, {'\0', '\0', (BYTE)255}, {{0, 0}, {4, 0}, {4, 4}, {3, 5}, {2, 4}, {1, 3}});
    Polygon2400 tryangle1({0, 0, 0, 0}, {(BYTE)255, '\0', '\0'}, {{0, 0}, {4, 0}, {4, 4}});
    //    poly1.initPolygon();
    //    This function is use a Personalize polygon

    cout << "Rect 2 (area: " << rect2.getArea()
         << ") intersects (61, 46): " << rect2.isIntersectPoint({61, 46})
         << endl;   // Should be true
    cout << "Rect 1 (area: " << rect1.getArea()
         << ") intersects (61, 41): " << rect1.isIntersectPoint({61, 46})
         << endl;   // Should be false

    //---------------------------------Circle---------------------------------
    cout << "Circle 1 (area: " << circle1.getArea()
         << ") should NOT intersect (50, 50) due to the nature of circles but: "
         << circle1.isIntersectPoint({50, 50}) << endl;
    cout << "Circle 2 (area: " << circle2.getArea()
         << ") intersects (70, 70): " << circle2.isIntersectPoint({70, 70}) << endl;
    //-------------------------------more tests-------------------------------
    cout << "Circle 2 (area: " << circle2.getArea()
         << ") intersects (60, 70): " << circle2.isIntersectPoint({60, 70}) << endl;
    cout << "Circle 2 (area: " << circle2.getArea()
         << ") intersects (59, 70): " << circle2.isIntersectPoint({59, 70}) << endl;
    cout << "Circle 2 (area: " << circle2.getArea()
         << ") intersects (61, 70): " << circle2.isIntersectPoint({61, 70}) << endl;

    //-------------------------------Polygon---------------------------------
    cout << "Polygon 1 (area: " << poly1.getArea()
         << ") intersects (0, 0): " << poly1.isIntersectPoint({100, 100}) << endl;
    cout << "Polygon 1 (area: " << poly1.getArea()
         << ") intersects (1, 1): " << poly1.isIntersectPoint({1, 1}) << endl;
    cout << "Triangle 1 (area: " << tryangle1.getArea()
         << ") intersects (0, 0): " << tryangle1.isIntersectPoint({100, 100}) << endl;

    cout << "------------Now put the shapes in an array and test again---------" << endl;
    // Put shapes in an array of Shape2400 POINTERS
    // Print the info again.  Make sure you get the SAME output....why might your code not work?
    // Use a breakpoint to see what version of getArea
    // or isIntersectPoint is called.
    Shape2400* ap_shapes[6];
    ap_shapes[0] = &rect1;
    ap_shapes[1] = &rect2;
    ap_shapes[2] = &circle1;
    ap_shapes[3] = &circle2;
    ap_shapes[4] = &poly1;
    ap_shapes[5] = &tryangle1;
    cout << "Rect 2 (area: " << ap_shapes[1]->getArea()
         << ") intersects (61, 46):" << ap_shapes[1]->isIntersectPoint({61, 46})
         << endl;   // Should be true
    cout << "Rect 1 (area: " << ap_shapes[0]->getArea()
         << ") intersects (61, 41):" << ap_shapes[0]->isIntersectPoint({61, 46})
         << endl;   // Should be false
    cout << "Circle 1 (area: " << ap_shapes[2]->getArea()
         << ") should NOT intersect (50, 50) due to the nature of circles but: "
         << ap_shapes[2]->isIntersectPoint({50, 50}) << endl;
    cout << "Circle 2 (area: " << ap_shapes[3]->getArea()
         << ") intersects (70, 70): " << ap_shapes[3]->isIntersectPoint({70, 70}) << endl;

    // Testing toString with a for loop
    for (int i = 0; i < 6; i++) {
        cout << "Shape " << i << " toString: " << ap_shapes[i]->toString() << endl;
    }

    return 0;
}
