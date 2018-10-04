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
        Vec axis2(7.07106781187, 7.07106781187, 0, DIRECTION);
        Vec referenceCity2(-3.535533905932738+50, 3.535533905932738+5, 0, POINT);
        Vec center2(50, 5, 0, POINT);
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
        ReferenceSystem r2(M_PI_4, 0, planet2.getR(),planet2.getRadio());

        ReferenceSystem planet2RS = planet2.getR();
        /*
        // Vec inUCS2 = planet2RS.changeReferenceSystem(r2.getOrigin());
        Matrix UCSMatrix(UCS);
        Matrix planet2RSMatrix(planet2RS);
        planet2RSMatrix.onlyDirections();
        planet2RSMatrix.transpose(); // ya se tiene la inversa

        Vec station2NewBase = planet2RSMatrix * r2.getOrigin(); // vectors aligned
        Vec center2Changed = planet2.getCenter();
        center2Changed.changeSign();
        Matrix translation(UCS);
        translation.translation(center2Changed);
        // translation.translation(planet2.getCenter());
        station2NewBase = translation*station2NewBase;

        station2NewBase = translate(planet2.getCenter(), station2NewBase);
        // Matrix aux = planet2RSMatrix.transpose();
         */

    // Vec inUCS2 = planet2RS.changeReferenceSystem(r2.getOrigin());
    Matrix UCSMatrix(UCS);
    Matrix planet2RSMatrix(planet2RS);
    planet2RSMatrix.onlyDirections();
    planet2RSMatrix.transpose(); // ya se tiene la inversa

    Vec center2Changed = planet2.getCenter();
    center2Changed.changeSign();
    Matrix translation(UCS);
    translation.translation(center2Changed); // translacion inversa

    Matrix changeBase = Matrix(planet2.getR());

    // Matrix cosa = translation*translation;
    //Vec newBase = translation*translation*planet2RSMatrix*r2.getOrigin();
    Vec aux1 = translation*r2.getOrigin();
    Vec aux2 = planet2RSMatrix*aux1;

    center2Changed = planet2.getCenter();
    translation.translation(center2Changed); // translacion inversa

    Vec aux3 = translation*aux2;

    Vec newBase = changeBase*translation*planet2RSMatrix*r2.getOrigin();

    //Vec inUCS2 = Matrix(UCS)*Matrix(planet2RS).transpose()*r2.getOrigin();

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