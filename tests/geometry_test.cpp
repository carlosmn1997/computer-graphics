#include "lest.hpp"
#include "../ReferenceSystem.h"
#include "../Planet.h"
#include "../Matrix.h"
#include "../exception.h"

using namespace std;

const lest::test matrixOperations[] =
        {
            CASE( "Determinant OK" )
            {
                float mat[4][4] =
                        {
                                {0, 0, 1, 6},
                                {0, 1, 0, 0},
                                {1, 0, 0, 0},
                                {0, 0, 0, 1}
                        };
                float det = Matrix::determinant(mat, 4);

                float mat2[4][4] =
                        {
                                {0.7, -0.7, 13, 5},
                                {12.5, 122, 0.1, 6},
                                {12.4, -1.2, -0.4, 7},
                                {12.4, 1.2, 0.4, 8}
                        };
                float det2 = Matrix::determinant(mat2, 4);
                EXPECT(det == -1);
                EXPECT(det2 -(-14756.6) < 0.01);
            },

            CASE( "Inverse matrix OK" )
            {
                float mat[4][4] =
                        {
                                {4, 0, 0, 0},
                                {0, 0, 2, 0},
                                {0, 1, 2, 0},
                                {1, 0, 0, 1}
                        };

                float inverseOk[4][4] =
                        {
                                {0.25, 0, 0, 0},
                                {0, -1, 1, 0},
                                {0, 0.5, 0, 0},
                                {-0.25, 0, 0, 1}
                        };
                Matrix inverseMatrixCalculated = Matrix(mat).inverse();
                Matrix inverseMatrixOk(inverseOk);

                EXPECT(inverseMatrixCalculated == inverseMatrixOk);
            },

            CASE( "Inclination out of range" )
            {
                Vec axis1(0, 10, 0, DIRECTION);
                Vec referenceCity1(3.535533905932738 + 1, 3.535533905932738, 0, POINT); // The radius is 5
                Vec center1(1, 0, 0, POINT);
                Planet planet1(center1, axis1, referenceCity1);
                ReferenceSystem r1(M_PI_2, 0, planet1.getR(), planet1.getRadio());

                EXPECT_THROWS( ReferenceSystem(M_PI*2, 0, r1, planet1.getRadio()) );
            },

            CASE( "Azimuth out of range" )
                {
                    Vec axis1(0, 10, 0, DIRECTION);
                    Vec referenceCity1(3.535533905932738 + 1, 3.535533905932738, 0, POINT); // The radius is 5
                    Vec center1(1, 0, 0, POINT);
                    Planet planet1(center1, axis1, referenceCity1);
                    ReferenceSystem r1(M_PI_2, 0, planet1.getR(), planet1.getRadio());

                    EXPECT_THROWS( ReferenceSystem(0, -M_PI*2, r1, planet1.getRadio()) );
                    EXPECT_THROWS( ReferenceSystem(0, M_PI*2, r1, planet1.getRadio()) );
                },
            CASE( "Radius not OK" )
            {
                Vec axis1(0, 10, 0, DIRECTION);
                Vec referenceCity1(10, 10, 0, POINT); // The radius is 5
                Vec center1(1, 0, 0, POINT);

                EXPECT_THROWS( Planet planet1(center1, axis1, referenceCity1) );
            }

        };

/*
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
*/

float calculateDistances(ReferenceSystem r1, ReferenceSystem r2){

    Vec distance = r2.getOrigin() - r1.getOrigin();

    return distance.modulus();

}


/*
 * p in UCS
 * return vector from r.origin to p
 */
Vec calculateVector(ReferenceSystem r, Vec p){

    Vec v;

    Matrix m = r.getMatrix();

    m = m.inverse();

    v = m * p;

    if(v.getZ()<0){
        throw(Exception("The launch can't go through matter or the object will be destroyed"));
    }

    v.setType(0.0);

    return v;

}

const lest::test TESTP[] =
        {
                CASE("Test 1: \"Planetas en linea\"") {

            ReferenceSystem UCS(Vec(1, 0, 0, DIRECTION),
                                Vec(0, 1, 0, DIRECTION),
                                Vec(0, 0, 1, DIRECTION),
                                Vec(0, 0, 0, POINT));

            // First planet
            Vec axis1(0, 10, 0, DIRECTION);
            Vec referenceCity1(3.535533905932738 + 1, 3.535533905932738, 0, POINT); // The radius is 5
            Vec center1(1, 0, 0, POINT);
            Planet planet1(center1, axis1, referenceCity1);

            // First ReferenceSystem
            //ReferenceSystem r1(M_PI, M_PI_2, planet1);
            ReferenceSystem r1(M_PI_2, 0, planet1.getR(), planet1.getRadio());
            Vec inUCS1 = r1.getOrigin(); // PUNTO EN UCS

            // Second planet
            //Vec axis2(0, 10, 0, DIRECTION);
            Vec axis2(7.07106781187, 7.07106781187, 0, DIRECTION);
            //Vec axis2(0, 10, 0, DIRECTION);
            //Vec referenceCity2(-15, -10, 0, POINT);
            Vec referenceCity2(-3.535533905932738 + 50, 3.535533905932738, 0, POINT);
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
            ReferenceSystem r2(3.0 * M_PI_4, 0, planet2.getR(), planet2.getRadio());
            Vec inUCS2 = r2.getOrigin(); // PUNTO EN UCS

            r2.setOrigin(inUCS2);
            r1.setOrigin(inUCS1);
            float distance = calculateDistances(r1, r2);

            Vec v1,v2;
            try {
                v1 = calculateVector(r1, inUCS2);
            }
            catch(Exception e){
                cout << e.getMessage() << endl;
                v1 = Vec(-1,-1,-1,DIRECTION);
            }

            try {
                v2 = calculateVector(r2, inUCS1);
            }
            catch(Exception e){
                cout << e.getMessage() << endl;
                v2 = Vec(-1,-1,-1,DIRECTION);
            }


            float diff = abs(distance - 39.0);

            float diff1 = abs(v1.getX() + v1.getY() + v1.getZ() - 39.0);

            float diff2 = abs(v2.getX() + v2.getY() + v2.getZ() - 39.0);

                    EXPECT(0.001 > diff);

                    EXPECT(0.001 > diff1);

                    EXPECT(0.001 > diff2);

            },

            CASE("Test 2: \"Lanzamiento cruza planeta\"") {
                    ReferenceSystem UCS(Vec(1, 0, 0, DIRECTION),
                                        Vec(0, 1, 0, DIRECTION),
                                        Vec(0, 0, 1, DIRECTION),
                                        Vec(0, 0, 0, POINT));

                    // First planet
                    Vec axis1(0, 10, 0, DIRECTION);
                    Vec referenceCity1(3.535533905932738 + 1, 3.535533905932738, 0, POINT); // The radius is 5
                    Vec center1(1, 0, 0, POINT);
                    Planet planet1(center1, axis1, referenceCity1);

                    // First ReferenceSystem
                    //ReferenceSystem r1(M_PI, M_PI_2, planet1);
                    ReferenceSystem r1(M_PI_2, 0, planet1.getR(), planet1.getRadio());
                    Vec inUCS1 = r1.getOrigin(); // PUNTO EN UCS

                    // Second planet
                    //Vec axis2(0, 10, 0, DIRECTION);
                    Vec axis2(7.07106781187*2, 7.07106781187*2, 0, DIRECTION);
                    //Vec axis2(0, 10, 0, DIRECTION);
                    //Vec referenceCity2(-15, -10, 0, POINT);
                    Vec referenceCity2(-3.535533905932738*2 + 50, 3.535533905932738*2+10, 0, POINT);
                    Vec center2(50, 10, 0, POINT);
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
                    ReferenceSystem r2(M_PI_4, M_PI, planet2.getR(), planet2.getRadio());
                    Vec inUCS2 = r2.getOrigin(); // PUNTO EN UCS

                    r2.setOrigin(inUCS2);
                    r1.setOrigin(inUCS1);
                    float distance = calculateDistances(r1, r2);

                    Vec v1, v2;
                    try {
                        v1 = calculateVector(r1, inUCS2);
                    }
                    catch(Exception e){
                        cout << e.getMessage() << endl;
                        v1 = Vec(-1,-1,-1,POINT);
                    }
                    try {
                        v2 = calculateVector(r2, inUCS1);
                    }
                    catch(Exception e){
                        cout << e.getMessage() << endl;
                        v2 = Vec(-1,-1,-1,POINT);
                    }
                    float diff = abs(distance - 54.918);

                    float diff1 = abs(v1.getX() + v1.getY() + v1.getZ() + v1.getType() - 64.0);

                    float diff2 = abs(v2.getX() + v2.getY() + v2.getZ() + v2.getType() + 2);

                    EXPECT(0.001 > diff);

                    EXPECT(0.001 > diff1);

                    EXPECT(0.001 > diff2);

                },

                CASE("Test 4: \"Otros dos planetas\"") {
                    ReferenceSystem UCS(Vec(1, 0, 0, DIRECTION),
                                        Vec(0, 1, 0, DIRECTION),
                                        Vec(0, 0, 1, DIRECTION),
                                        Vec(0, 0, 0, POINT));

                    // First planet
                    Vec axis1(0, 0, 10, DIRECTION);
                    Vec referenceCity1(-15, 20, 0, POINT); // The radius is 5
                    Vec center1(-15, 15, 0, POINT);
                    Planet planet1(center1, axis1, referenceCity1);

                    // First ReferenceSystem
                    //ReferenceSystem r1(M_PI, M_PI_2, planet1);
                    ReferenceSystem r1(M_PI_2, M_PI_2, planet1.getR(), planet1.getRadio());
                    Vec inUCS1 = r1.getOrigin(); // PUNTO EN UCS

                    // Second planet
                    //Vec axis2(0, 10, 0, DIRECTION);
                    Vec axis2(7.07106781187, 7.07106781187, 0, DIRECTION);
                    //Vec axis2(0, 10, 0, DIRECTION);
                    //Vec referenceCity2(-15, -10, 0, POINT);
                    Vec referenceCity2(-3.535533905932738 + 15, 3.535533905932738-15, 0, POINT);
                    Vec center2(15, -15, 0, POINT);
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
                    ReferenceSystem r2(3.0*M_PI_4, 0, planet2.getR(), planet2.getRadio());
                    Vec inUCS2 = r2.getOrigin(); // PUNTO EN UCS

                    r2.setOrigin(inUCS2);
                    r1.setOrigin(inUCS1);
                    float distance = calculateDistances(r1, r2);

                    Vec v1, v2;
                    try {
                        v1 = calculateVector(r1, inUCS2);
                    }
                    catch(Exception e){
                        cout << e.getMessage() << endl;
                        v1 = Vec(-1,-1,-1,POINT);
                    }
                    try {
                        v2 = calculateVector(r2, inUCS1);
                    }
                    catch(Exception e){
                        cout << e.getMessage() << endl;
                        v2 = Vec(-1,-1,-1,POINT);
                    }
                    float diff = abs(distance - 36.0555);


                    EXPECT(0.001 > diff);


                },

                CASE("Test 3: \"Estaciones en los polos\"") {
                    ReferenceSystem UCS(Vec(1, 0, 0, DIRECTION),
                                        Vec(0, 1, 0, DIRECTION),
                                        Vec(0, 0, 1, DIRECTION),
                                        Vec(0, 0, 0, POINT));

                    // First planet
                    Vec axis1(0, 10, 0, DIRECTION);
                    Vec referenceCity1(-3.535533905932738 + 1, -3.535533905932738, 0, POINT); // The radius is 5
                    Vec center1(1, 0, 0, POINT);
                    Planet planet1(center1, axis1, referenceCity1);

                    // First ReferenceSystem
                    //ReferenceSystem r1(M_PI, M_PI_2, planet1);
                    ReferenceSystem r1(0, M_PI_2, planet1.getR(), planet1.getRadio());
                    Vec inUCS1 = r1.getOrigin(); // PUNTO EN UCS

                    // Second planet
                    //Vec axis2(0, 10, 0, DIRECTION);
                    Vec axis2(7.07106781187*2, 7.07106781187*2, 0, DIRECTION);
                    //Vec axis2(0, 10, 0, DIRECTION);
                    //Vec referenceCity2(-15, -10, 0, POINT);
                    Vec referenceCity2(-3.535533905932738*2 + 1, 3.535533905932738*2+65, 0, POINT);
                    Vec center2(1, 65, 0, POINT);
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
                    ReferenceSystem r2(3*M_PI_4, M_PI, planet2.getR(), planet2.getRadio());
                    Vec inUCS2 = r2.getOrigin(); // PUNTO EN UCS

                    r2.setOrigin(inUCS2);
                    r1.setOrigin(inUCS1);
                    float distance = calculateDistances(r1, r2);

                    Vec v1, v2;
                    try {
                        v1 = calculateVector(r1, inUCS2);
                    }
                    catch(Exception e){
                        cout << e.getMessage() << endl;
                        v1 = Vec(-1,-1,-1,POINT);
                    }
                    try {
                        v2 = calculateVector(r2, inUCS1);
                    }
                    catch(Exception e){
                        cout << e.getMessage() << endl;
                        v2 = Vec(-1,-1,-1,POINT);
                    }
                    float diff = abs(distance - 50);

                    float diff1 = abs(v1.getX() + v1.getY() + v1.getZ() + v1.getType() - 50);

                    float diff2 = abs(v2.getX() + v2.getY() + v2.getZ() + v2.getType() - 50);

                            EXPECT(0.001 > diff);

                            EXPECT(0.001 > diff1);

                            EXPECT(0.001 > diff2);

                }
        };

int main( int argc, char * argv[] )
{
    lest::run(matrixOperations, argc, argv);

    try {

        return lest::run( TESTP, argc, argv );
    }
    catch(Exception e){
        cout << e.getMessage() << endl;
    }
}