#include <iostream>
#include "Vec.h"
#include "geometry.h"
#include "Planet.h"
#include "ReferenceSystem.h"

#include <cmath>

using namespace std;

void example1() {
    // First planet
    Vec axis1(15, 5, 10, DIRECTION);
    Vec referenceCity1(5, 15, 10, POINT);
    Vec center1(10, 10, 10, POINT);
    Planet planet1(center1, axis1, referenceCity1);

    // First ReferenceSystem
    ReferenceSystem(M_PI, M_PI_2, planet1);
}

int main() {
    Vec vec(1, 2, 3, DIRECTION);
    cout << vec;
    cout << nada();
    example1();
    return 0;
}