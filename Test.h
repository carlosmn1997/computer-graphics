//
// Created by Nicolas on 01/10/2018.
//

#include "DistanceCalculator.h"


class Test{

public:
    void executeTest(){
        cout<<"EXAMPLE 1"<<endl;
        example1();
        cout<<"EXAMPLE 2"<<endl;
       // example2();
    }

    void example1() {
        // First planet
        Vec axis1(0, 10, 0, DIRECTION);
        Vec referenceCity1(3.535533905932738, 3.535533905932738, 0, POINT); // The radius is 5
        Vec center1(0, 0, 0, POINT);
        Planet planet1(center1, axis1, referenceCity1);

        // First ReferenceSystem
        //ReferenceSystem r1(M_PI, M_PI_2, planet1);
        ReferenceSystem r1(M_PI_2, 0, planet1.getR(),planet1.getRadio());
        //Vec inUCS = r1.changeReferenceSystem()

        // Second planet
        /*
        Vec axis2(0, 10, 0, DIRECTION);
        Vec referenceCity2(-3.535533905932738+50, 3.535533905932738, 0, POINT);
        Vec center2(50, 0, 0, POINT);
        Planet planet2(center2, axis2, referenceCity2);

        // Second ReferenceSystem
        ReferenceSystem r2(M_PI_2, -M_PI_2, planet2);

        calculateDistances(r1,r2);

        // Si la distancia Origen o destino, la coordenada K es NEGATIVA,
        // entonces la trayectoria pasa por el propio planeta
        */

    }
/*
    void example2(){//Los planetas estan uno "encima" de otro y cada estacion en un polo
        Vec axis1(0, 20, 0, DIRECTION);
        Vec referenceCity1(0, 7.07106781, 7.07106781, POINT); // The radius is 10
        Vec center1(0, 0, 0, POINT);
        Planet planet1(center1, axis1, referenceCity1);

        // First ReferenceSystem
        //ReferenceSystem r1(M_PI, M_PI_2, planet1);
        ReferenceSystem r1(M_PI, 1, planet1);

        // Second planet
        Vec axis2(0, 10, 0, DIRECTION);
        Vec referenceCity2(3.535533905932738, 3.535533905932738-50, 0, POINT); // The radius is 5
        Vec center2(0, -50, 0, POINT);
        Planet planet2(center2, axis2, referenceCity2);

        // Second ReferenceSystem
        ReferenceSystem r2(0, 1, planet2);

        cout<<"DISTANCE 2a"<<endl;
        calculateDistances(r1,r2);

        ReferenceSystem r1aux(M_PI, -M_PI_2, planet1);
        ReferenceSystem r2aux(0, M_PI_2, planet2);

        cout<<"DISTANCE 2b"<<endl;
        calculateDistances(r1aux,r2aux);

        cout<<endl<<"THE 2A AND 2B MUST BE THE SAME"<<endl<<endl;

    }

    void example3() { // Se atraviesa planeta origen
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
        Vec referenceCity2(3.535533905932738+50, 3.535533905932738, 0, POINT);
        Vec center2(50, 0, 0, POINT);
        Planet planet2(center2, axis2, referenceCity2);

        // Second ReferenceSystem
        ReferenceSystem r2(M_PI_2, -M_PI_2, planet2);

        calculateDistances(r1,r2);

        // Si la distancia Origen o destino, la coordenada K es NEGATIVA,
        // entonces la trayectoria pasa por el propio planeta

    }
*/
};