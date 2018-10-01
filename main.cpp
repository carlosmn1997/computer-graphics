#include <iostream>
#include "Vec.h"
#include "geometry.h"
#include "Planet.h"
#include "ReferenceSystem.h"

#include <cmath>

using namespace std;

void example1() {
    // First planet
    Vec axis1(0, 10, 0, DIRECTION);
    Vec referenceCity1(3.535533905932738, 3.535533905932738, 0, POINT); // The radius is 5
    Vec center1(0, 0, 0, POINT);
    Planet planet1(center1, axis1, referenceCity1);

    // First ReferenceSystem
    //ReferenceSystem r1(M_PI, M_PI_2, planet1);
    ReferenceSystem r1(M_PI_2, M_PI_2, planet1);

    // Second planet
    Vec axis2(0, 10, 0, DIRECTION);
    Vec referenceCity2(-3.535533905932738+50, 3.535533905932738, 0, POINT);
    Vec center2(50, 0, 0, POINT);
    Planet planet2(center2, axis2, referenceCity2);

    // Second ReferenceSystem
    ReferenceSystem r2(M_PI_2, -M_PI_2, planet2);

    Vec distance = r2.getCenter() - r1.getCenter();

    cout << "Distancia UCS: " << distance << endl;
    Vec distanceOrigin = r1.changeReferenceSystem(distance);
    cout << "Distancia Origen: " << distanceOrigin << endl;
    Vec distanceDestiny = r2.changeReferenceSystem(distance);
    cout << "Distancia Destino: " << distanceDestiny << endl;
    // Si la distancia Origen o destino, la coordenada K es NEGATIVA,
    // entonces la trayectoria pasa por el propio planeta

}

int main() {
    example1();
    return 0;
}