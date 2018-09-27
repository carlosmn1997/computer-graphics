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
    ReferenceSystem r1(M_PI, M_PI_2, planet1);

    // Second planet
    Vec axis2(30, 5, 10, DIRECTION);
    Vec referenceCity2(30, 15, 10, POINT);
    Vec center2(30, 10, 10, POINT);
    Planet planet2(center2, axis2, referenceCity2);

    // Second ReferenceSystem
    ReferenceSystem r2(M_PI, M_PI_2, planet2);

    Vec distance = r2.getCenter() - r1.getCenter();

    cout << "Distancia UCS: " << distance << endl;
    Vec distanceOrigin = r1.changeReferenceSystem(distance);
    cout << "Distancia Origen: " << distanceOrigin << endl;
    Vec distanceDestiny = r2.changeReferenceSystem(distance);
    cout << "Distancia Destino: " << distanceDestiny << endl;
}

int main() {
    example1();
    return 0;
}