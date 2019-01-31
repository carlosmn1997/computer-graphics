#include "lest.hpp"
#include "../Image.h"

using namespace std;

const lest::test toneMapping[] =
        {
            CASE( "Tone Mapping" )
            {

                Image image("../cornellPuntual100.ppm");
                //image.clamping();
                //image.equalization();
                image.gammaCurve(2.5);
                //image.equalizeAndClamp();
                //image.gammaCurveClamping(2.5);
                //image.Reinhard();
                image.writeImage();
                cout << "fin" << endl;
                EXPECT(0.001 > 0.002);
            }

        };

int main( int argc, char * argv[] )
{
    return lest::run( toneMapping, argc, argv );
}