#include "lest.hpp"
#include "../Image.h"

using namespace std;

const lest::test toneMapping[] =
        {
            CASE( "Tone Mapping" )
            {

                Image image("mpi_atrium_1.ppm");
                image.writeImage();
                EXPECT(0.001 > 0.002);
            }

        };

int main( int argc, char * argv[] )
{
    return lest::run( toneMapping, argc, argv );
}