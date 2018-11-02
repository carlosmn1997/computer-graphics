#include "../Plane.h"
#include "lest.hpp"

using namespace std;

const lest::test PLANE[] =
        {
                CASE( "Intercepta" )
                {
                    Vec o(10,0,0,1);
                    Vec n(-0.70710678118,0.70710678118,0,0);
                    RGB r(255,0,0);
                    Plane pla(o,n,r);
                    Vec v(1,0,0,0);
                    Vec p(0,0,0,1);
                    bool b = pla.intercepts(v);
                    Vec inte = pla.intPoint(v,p);
                    float f = abs(10 - inte.getX());
                    EXPECT(!b);
                    EXPECT(f<0.0001);
                }

        };

int main( int argc, char * argv[] )
{
    return lest::run( PLANE, argc, argv );
}