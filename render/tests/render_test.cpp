#include <ostream>
#include "../Render.h"
#include "../Light.h"

using namespace std;

void rayTracingExample(){
   Vec l(-128,0,0,0);
   Vec u(0,72,0,0);
   Vec f(0,0,100,0);
   Vec o(0,0,0,1);
   Render r(u,l,f,o);
   Vec origin1(0,0,250,1);
   Vec normal(0,0,-1,0);
   Plane p(origin1,normal,RGB(255,0,0));
   r.addPlane(p);
   Vec origin2(0,-100,0,1);
   Vec normal2(0,1,0,0);
   Plane q(origin2,normal2,RGB(0,255,0));
   r.addPlane(q);
   Vec origin3(0,100,0,1);
   Vec normal3(0,-1,0,0);
   Plane t(origin3,normal3,RGB(0,0,255));
   r.addPlane(t);
   Vec origin4(150,0,0,1);
   Vec normal4(-1,0,0,0);
   Plane w(origin4,normal4,RGB(5,5,5));
   r.addPlane(w);
   Vec origin5(-200,0,0,1);
   Vec normal5(1,0,0,0);
   Plane v(origin5,normal5,RGB(255,255,255));
   r.addPlane(v);
   Vec centre(0,0,200,1);
   Vec axis(0,100,0,0);
   Vec refCity(0,0,150,1);
   Sphere sph(centre,axis,refCity);
   sph.setProps(RGB(80,80,80));
   r.addSphere(sph);
   r.trazar();
   cout<<"acabo y escribo"<<endl;
   r.escribirImagen("nombre.ppm");
}

void pathTracer1(){
   Vec l(-128,0,0,0);
   Vec u(0,72,0,0);
   Vec f(0,0,100,0);
   Vec o(0,0,0,1);
   Render r(u,l,f,o);
   Vec origin1(0,0,250,1);
   Vec normal(0,0,-1,0);
   Plane p(origin1,normal,RGB(0,0,0));
   p.setKd(RGB(0.8, 0.1, 0.1));
   //Plane p(origin1,normal,RGB(0.254,0.031,0.031));
   r.addPlane(p);

   Vec origin2(0,-100,0,1);
   Vec normal2(0,0,1,0);
   Plane q(origin2,normal2,RGB(0,0,0));
   q.setKd(RGB(0.1, 0.8, 0.1));
   r.addPlane(q);
   Vec origin3(0,100,0,1);
   Vec normal3(0,0,-1,0);
   Plane t(origin3,normal3,RGB(1000,1000,1000));
   t.setKd(RGB(0, 0, 0));
   r.addPlane(t);

   r.trazar();
   cout<<"acabo y escribo"<<endl;
   r.escribirImagen("nombre.ppm");
}

void pathTracer2(){
   Vec l(-128,0,0,0);
   Vec u(0,72,0,0);
   Vec f(0,0,100,0);
   Vec o(0,0,0,1);
   Render r(u,l,f,o);
   Vec origin1(0,0,250,1);
   Vec normal(0,0,-1,0);
   // Fondo rojo
   Plane p(origin1,normal,RGB(0,0,0));
   p.setKd(RGB(0.8, 0.1, 0.1));
   r.addPlane(p);
   Vec origin2(0,-100,0,1);
   Vec normal2(0,1,0,0);
   // Techo azul
   Plane q(origin2,normal2,RGB(0,0,0));
   q.setKd(RGB(0.1, 0.8, 0.1));
   r.addPlane(q);
   Vec origin3(0,100,0,1);
   Vec normal3(0,-1,0,0);
   // Suelo emisor blanco
   Plane t(origin3,normal3,RGB(255,255,255));
   t.setKd(RGB(0, 0, 0));
   r.addPlane(t);
   r.trazar();
   cout<<"acabo y escribo"<<endl;
   r.escribirImagen("nombre.ppm");
}

void pathTracer3(){
   Vec l(-128,0,0,0);
   Vec u(0,72,0,0);
   Vec f(0,0,100,0);
   Vec o(0,0,0,1);
   Render r(u,l,f,o);
   Vec origin1(0,0,250,1);
   Vec normal(0,0,-1,0);
   // Fondo
   Plane p(origin1,normal,RGB(0,0,0));
   p.setKd(RGB(0.8,0.1,0.1));
   p.setKs(RGB(0.2,0.2,0.2));
   p.setAlpha(0.2);
   r.addPlane(p);
   Vec origin2(0,-100,0,1);
   Vec normal2(0,1,0,0);
   // Suelo
   Plane q(origin2,normal2,RGB(0,0,0));
   q.setKd(RGB(0.8,0.8,0.8));
   q.setKs(RGB(0.2,0.2,0.2));
   q.setAlpha(0.2);
   r.addPlane(q);
   Vec origin3(0,100,0,1);
   Vec normal3(0,-1,0,0);
   // Techo
   Plane t(origin3,normal3,RGB(0, 0,0));
   t.setKd(RGB(0.1,0.1,0.8));
   t.setKs(RGB(0.2,0.2,0.2));
   t.setAlpha(0.2);
   r.addPlane(t);
   // Plano derecha
   Vec origin4(150,0,0,1);
   Vec normal4(-1,0,0,0);
   Plane v(origin4,normal4,RGB(0, 0,0));
   v.setKd(RGB(0.1,0.8,0.1));
   v.setKs(RGB(0.2,0.2,0.2));
   v.setAlpha(0.2);
   r.addPlane(v);
   // Plano izquierda
    Vec origin5(-150,0,0,1);
    Vec normal5(1,0,0,0);
    Plane w(origin5,normal5,RGB(0, 0,0));
    w.setKd(RGB(0.1,0.8,0.1));
    w.setKs(RGB(0.2,0.2,0.2));
    w.setAlpha(0.2);
   r.addPlane(w);
   Vec center(0,-60,175,1);
   Vec normal6(0,80,0,0);
   Vec refCity(0,-60,135,1);
   Sphere s(center,normal6,refCity);
   s.setKd(RGB(0.1,0.8,0.1));
   s.setKs(RGB(0.2,0.2,0.2));
   s.setAlpha(0.2);
    r.addSphere(s);

    // Luz
   Light luz(1000000000, Vec(0, 0, 150, POINT));
   r.addLight(luz);

   r.trazar();
   cout<<"acabo y escribo"<<endl;
   r.escribirImagen("nombre.ppm");
}


int main( int argc, char * argv[] )
{
   //rayTracingExample();
   pathTracer3();
   return 0;
}