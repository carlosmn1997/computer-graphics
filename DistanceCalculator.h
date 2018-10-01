//
// Created by Nicolas on 01/10/2018.
//

#ifndef COMPUTER_GRAPHICS_DISTANCECALCULATOR_H
#define COMPUTER_GRAPHICS_DISTANCECALCULATOR_H

#include <iostream>
#include "Vec.h"
#include "geometry.h"
#include "Planet.h"
#include "ReferenceSystem.h"

using namespace std;


void calculateDistances(ReferenceSystem r1, ReferenceSystem r2){

        Vec distance = r2.getOrigin() - r1.getOrigin();

        cout << "Distancia UCS: " << distance << endl;
        Vec distanceOrigin = r1.changeReferenceSystem(distance);
        cout << "Distancia Origen: " << distanceOrigin << endl;
        Vec distanceDestiny = r2.changeReferenceSystem(distance);
        cout << "Distancia Destino: " << distanceDestiny << endl << endl;

        if(distanceOrigin.getZ()<0){
            std::cout<< "ERORR: The transported matter would go through the origin planet";
            std::exit(1);
        }
        else if(distanceDestiny.getZ()<0){
            std::cout<< "ERORR: The transported matter would go through the destination planet";
            std::exit(1);
        }

}

#endif //COMPUTER_GRAPHICS_DISTANCECALCULATOR_H
