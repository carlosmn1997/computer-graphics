#include <ostream>
#include "../Render.h"

using namespace std;

int main( int argc, char * argv[] )
{
   Vec l(144,0,0,0);
   Vec u(0,256,0,0);
   Vec f(0,0,100,0);
   Vec o(0,0,0,1);
   Render r(u,l,f,o);
   Vec origin1(0,0,400,1);
   Vec normal(0,0,-1,0);
   Plane p(origin1,normal,RGB(255,0,0));
   r.addPlane(p);
   Vec origin2(0,-72,0,1);
   Vec normal2(0,1,0,0);
   Plane q(origin2,normal2,RGB(0,255,0));
   r.addPlane(q);
   Vec center(0, 0, 250, 1);
   Vec axis(0, 10, 0, 0);
   Vec refCity(0, 0, 255, 1);
   Sphere s(center, axis, refCity);
   s.setProps(RGB(0,0,255));
   //r.addSphere(s);
   r.trazar();
   cout<<"acabo y escribo"<<endl;
   r.escribirImagen("nombre.ppm");
   return 0;
}