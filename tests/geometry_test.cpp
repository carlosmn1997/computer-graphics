#include "lest.hpp"
#include "../ReferenceSystem.h"
#include "../Planet.h"
#include "../Matrix.h"

using namespace std;



const lest::test specification[] =
        {
                CASE( "Empty string has length zero (succeed)" )
                {
                            EXPECT( 0 == string(  ).length() );
                            EXPECT( 0 == string("").length() );
                },

                CASE( "Text compares lexically (fail)" )
                {
                            EXPECT( string("hello") > string("world") );
                },

                CASE( "Unexpected exception is reported" )
                {
                            EXPECT( (throw std::runtime_error("surprise!"), true) );
                },

                CASE( "Unspecified expected exception is captured" )
                {
                            EXPECT_THROWS( throw std::runtime_error("surprise!") );
                },

                CASE( "Specified expected exception is captured" )
                {
                            EXPECT_THROWS_AS( throw std::bad_alloc(), std::bad_alloc );
                },

                CASE( "Expected exception is reported missing" )
                {
                            EXPECT_THROWS( true );
                },

                CASE( "Specific expected exception is reported missing" )
                {
                            EXPECT_THROWS_AS( true, std::runtime_error );
                },
        };

float calculateDistances(ReferenceSystem r1, ReferenceSystem r2){

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

    return distance.modulus();

}

Vec calculateVector(ReferenceSystem referenceSystem, Vec p){

}

const lest::test TESTP[] =
        {
                CASE( "Test 1: \"Planetas en linea\" ejecutado correctamente" )
                {

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
                    Vec center2(50, 0, 0, POINT);
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
                    ReferenceSystem r2(3.0*M_PI_4, 0, planet2.getR(),planet2.getRadio());

                    ReferenceSystem planet2RS = planet2.getR();

                    Vec center2Changed = planet2.getCenter();
                    center2Changed.changeSign();
                    Matrix translation(UCS);
                    translation.translation(center2Changed);

                    Vec inCenter = translation * r2.getOrigin();
                    Vec inUCS2 = Matrix(planet2RS) * inCenter; // PUNTO EN UCS


                    float distance = calculateDistances(r1,r2);

                    Vec v1 = calculateVector(r1,inUCS);

                    Vec v2 = calculateVector(r2,inUCS2);

                    float diff = abs(distance - 36.0);

                    float diff1 = abs(v1.getZ() + v1.getY() + v1.getZ() - 36.0);

                    float diff2 = abs(v2.getZ() + v2.getY() + v2.getZ() - 36.0);

                    EXPECT( 0.001 > diff );

                    EXPECT( 0.001 > diff1 );

                    EXPECT( 0.001 > diff2 );

                },
        };

int main( int argc, char * argv[] )
{
    return lest::run( specification, argc, argv );
}