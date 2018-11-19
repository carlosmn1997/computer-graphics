#include <ostream>
#include "../Render.h"

using namespace std;

int main( int argc, char * argv[] )
{
   Vec l(-128,0,0,0);
   Vec u(0,72,0,0);
   Vec f(0,0,100,0);
   Vec o(0,0,0,1);
   Render r(u,l,f,o);
   Vec origin1(0,0,250,1);
   Vec normal(0,0,-1,0);
   Plane p(origin1,normal,RGB(0.254,0.031,0.031));
   r.addPlane(p);
   /*
   Vec origin2(0,-100,0,1);
   Vec normal2(0,1,0,0);
   Plane q(origin2,normal2,RGB(0,255,0));
   r.addPlane(q);
   Vec origin3(0,100,0,1);
   Vec normal3(0,-1,0,0);
   Plane t(origin3,normal3,RGB(0,0,255));
   r.addPlane(t);
    */
   r.trazar();
   cout<<"acabo y escribo"<<endl;
   r.escribirImagen("nombre.ppm");
   return 0;
}