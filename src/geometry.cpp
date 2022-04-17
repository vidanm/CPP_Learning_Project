#include "geometry.hpp"

void test_generic_points()
{
    /*
    Point<...> p1;
    Point<...> p2;
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3;
    */

    Point<2, int> p1;
    Point<2, int> p2;
    auto p3 = p1 + p2;
    p1 += p2;
    p3 *= 3;

    Point<3, double> p4;
    Point<3, double> p5;
    auto p6 = p4 + p5;
    p4 += p5;
    p6 *= 3;
}