//
// Created by Nicolas on 01/10/2018.
//

#ifndef COMPUTER_GRAPHICS_TEST_H
#define COMPUTER_GRAPHICS_TEST_H

#include "DistanceCalculator.h"
#include "Matrix.h"



class Test{

public:
    void executeTest(){
        cout<<"EXAMPLE 1"<<endl;
        example1();
        cout<<"EXAMPLE 2"<<endl;
       // example2();
        //examplePoles();
    }

    void examplePoles(){
        cout <<"Checking a reference city can't be in one of the poles"<< endl;
        Vec axis2(7.07106781187, 7.07106781187, 0, DIRECTION);
        Vec referenceCity2(-3.535533905932738+10, -3.535533905932738+10, 0, POINT);
        Vec center2(10, 10, 0, POINT);
        Planet planet2(center2, axis2, referenceCity2);
    }

    void example1() {
        // ReferenceSystem UCS()
        ReferenceSystem UCS(Vec(1,0,0, DIRECTION),
                Vec(0,1,0,DIRECTION),
                Vec(0,0,1,DIRECTION),
                Vec(0,0,0,POINT));

        // First planet
        Vec axis1(0, 10, 0, DIRECTION);
        Vec referenceCity1(3.535533905932738+1, 3.535533905932738, 0, POINT); // The radius is 5
        Vec center1(1, 0, 0, POINT);
        Planet planet1(center1, axis1, referenceCity1);

        // First ReferenceSystem
        //ReferenceSystem r1(M_PI, M_PI_2, planet1);
        ReferenceSystem r1(M_PI_2, 0, planet1.getR(),planet1.getRadio());


        ReferenceSystem planetRS = planet1.getR();
        Vec inUCS = planetRS.changeReferenceSystem(r1.getOrigin());

        // Second planet
        //Vec axis2(0, 10, 0, DIRECTION);
        Vec axis2(7.07106781187, 7.07106781187, 0, DIRECTION);
        //Vec axis2(0, 10, 0, DIRECTION);
        //Vec referenceCity2(-15, -10, 0, POINT);
        Vec referenceCity2(-3.535533905932738+10, 3.535533905932738+10, 0, POINT);
        Vec center2(10, 10, 0, POINT);
        Planet planet2(center2, axis2, referenceCity2);

        /*
        // Second ReferenceSystem
        ReferenceSystem r2(M_PI_2, 0, planet2.getR(),planet2.getRadio());

        Vec axis2(0, 10, 0, DIRECTION);
        Vec referenceCity2(3.535533905932738-50, 3.535533905932738+5, 0, POINT);
        Vec center2(-50, 5, 0, POINT);
        Planet planet2(center2, axis2, referenceCity2);

         */
        // Second ReferenceSystem
        ReferenceSystem r2(M_PI_2, M_PI, planet2.getR(),planet2.getRadio());

        ReferenceSystem planet2RS = planet2.getR();

        Vec center2Changed = planet2.getCenter();
        center2Changed.changeSign();
        Matrix translation(UCS);
        translation.translation(center2Changed);

        Vec inCenter = translation * r2.getOrigin();
        Vec inUCS2 = Matrix(planet2RS) * inCenter; // PUNTO EN UCS


    calculateDistances(r1,r2);

    // Si la distancia Origen o destino, la coordenada K es NEGATIVA,
    // entonces la trayectoria pasa por el propio planeta

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

#endif