#include <ostream>
#include "../Render.h"
#include "../Light.h"
#include <ctime>

using namespace std;
/*
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
*/
/*
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
*/

/*
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
*/
void pathTracer3(int numpaths){
    Vec l(-12.8,0,0,0);
    Vec u(0,7.2,0,0);
    Vec f(0,0,15,0);
    Vec o(0,0,0,1);
    Render r(720,1280,u,l,f,o);
    Vec origin1(0,0,30,1);
    Vec normal(0,0,-1,0);
    // Fondo
    Plane p(origin1,normal,RGB(0,0,0));
    p.setKd(RGB(0.5,0.5,0.5));
    p.setKs(RGB(0,0,0));
    p.setKsp(RGB(0,0,0));
    p.setKr(RGB(0,0,0));
    p.setAlpha(0);
    r.addPlane(p);
    Vec origin2(0,-10,0,1);
    Vec normal2(0,1,0,0);
    // Suelo
    Plane q(origin2,normal2,RGB(0,0,0));
    q.setKd(RGB(0.5,0.5,0.5));
    q.setKs(RGB(0,0,0));
    q.setKsp(RGB(0,0,0));
    q.setKr(RGB(0,0,0));
    q.setAlpha(0.2);
    r.addPlane(q);
    Vec origin3(0,10,0,1);
    Vec normal3(0,-1,0,0);
    // Techo
    //Plane t(origin3,normal3,RGB(1000, 1000, 1000));
    //Plane t(origin3,normal3,RGB(0, 0, 0));
    Plane t(origin3,normal3,RGB(255, 255, 255));
    //t.setKd(RGB(0.5,0.5,0.5));
    t.setKd(RGB(0,0,0));
    t.setKs(RGB(0,0,0));
    t.setKsp(RGB(0,0,0));
    t.setKr(RGB(0,0,0));
    t.setAlpha(0.2);
    r.addPlane(t);
    // Plano izquierda
    Vec origin4(15,0,0,1);
    Vec normal4(-1,0,0,0);
    Plane v(origin4,normal4,RGB(0, 0,0));
    v.setKd(RGB(0.5,0.1,0.1));
    v.setKs(RGB(0,0,0));
    v.setKsp(RGB(0,0,0));
    v.setKr(RGB(0,0,0));
    v.setAlpha(0.2);
    r.addPlane(v);
    // Plano derecha
    Vec origin5(-5,0,0,1);
    Vec normal5(1,0,0,0);
    Plane w(origin5,normal5,RGB(0, 0,0));
    w.setKd(RGB(0.1,0.5,0.1));
    w.setKs(RGB(0,0,0));
    w.setKsp(RGB(0,0,0));
    w.setKr(RGB(0,0,0));
    w.setAlpha(0.2);
    r.addPlane(w);
    // Pelota
    Vec center(0,-6,25,1);
    Vec normal6(0,6,0,0);
    Vec refCity(0,-6,22,1);
    Sphere s(center,normal6,refCity);
    s.setKd(RGB(0.5,0.5,0));
    s.setKs(RGB(0.7,0.7,0.6));
    s.setKsp(RGB(0,0,0));
    s.setKr(RGB(0,0,0));
    s.setAlpha(0.02);
    r.addSphere(s);

    // Espejito magico
    Vec center2(0,-6,25,1);
    Vec normal7(0,6,0,0);
    Vec refCity2(0,-6,22,1);
    Sphere s2(center2,normal7,refCity2);
    s2.setKd(RGB(0,0,0));
    s2.setKs(RGB(0,0,0));
    s2.setKsp(RGB(1,1,1));
    s2.setKr(RGB(0,0,0));
    s2.setAlpha(0);
    //r.addSphere(s2);

    // Luz
    //Light luz(100000000, Vec(10, 1, 15, POINT));
    Light luz(1000000, Vec(10, 5, 15, POINT));
    //r.addLight(luz);

    r.trazar(numpaths);
    cout<<"acabo y escribo"<<endl;
    r.escribirImagen("nombre.ppm");
}

void pathTracerCornellBox1(int numpaths){
    Vec l(-12.8,0,0,0);
    Vec u(0,7.2,0,0);
    Vec f(0,0,15,0);
    Vec o(0,0,0,1);
    Render r(720,1280,u,l,f,o);
    Vec origin1(0,0,45,1);
    Vec normal(0,0,-1,0);
    // Fondo
    Plane p(origin1,normal,RGB(0,0,0));
    p.setKd(RGB(0.1,0.1,0.5));
    p.setKs(RGB(0,0,0));
    p.setKsp(RGB(0,0,0));
    p.setKr(RGB(0,0,0));
    p.setAlpha(0);
    r.addPlane(p);
    Vec origin2(0,-10,0,1);
    Vec normal2(0,1,0,0);
    // Suelo
    Plane q(origin2,normal2,RGB(0,0,0));
    q.setKd(RGB(0.5,0.5,0.5));
    q.setKs(RGB(0,0,0));
    q.setKsp(RGB(0,0,0));
    q.setKr(RGB(0,0,0));
    q.setAlpha(0.2);
    r.addPlane(q);
    Vec origin3(0,10,0,1);
    Vec normal3(0,-1,0,0);
    // Techo
    //Plane t(origin3,normal3,RGB(1000, 1000, 1000));
    //Plane t(origin3,normal3,RGB(0, 0, 0));
    Plane t(origin3,normal3,RGB(0, 0, 0));
    t.setKd(RGB(0.5,0.5,0.5));
    //t.setKd(RGB(0,0,0));
    t.setKs(RGB(0,0,0));
    t.setKsp(RGB(0,0,0));
    t.setKr(RGB(0,0,0));
    t.setAlpha(0.2);
    r.addPlane(t);
    // Plano izquierda
    Vec origin4(15,0,0,1);
    Vec normal4(-1,0,0,0);
    Plane v(origin4,normal4,RGB(0, 0,0));
    v.setKd(RGB(0.5,0.1,0.1));
    v.setKs(RGB(0,0,0));
    v.setKsp(RGB(0,0,0));
    v.setKr(RGB(0,0,0));
    v.setAlpha(0.2);
    r.addPlane(v);
    // Plano derecha
    Vec origin5(-15,0,0,1);
    Vec normal5(1,0,0,0);
    Plane w(origin5,normal5,RGB(0, 0,0));
    w.setKd(RGB(0.1,0.5,0.1));
    w.setKs(RGB(0,0,0));
    w.setKsp(RGB(0,0,0));
    w.setKr(RGB(0,0,0));
    w.setAlpha(0.2);
    r.addPlane(w);

    // Pelota Plastico
    Vec center(5,-5,25,1);
    Vec normal6(0,6,0,0);
    Vec refCity(5,-5,22,1);
    Sphere s(center,normal6,refCity);
    s.setKd(RGB(0.4,0.4,0));
    s.setKs(RGB(0.6,0.6,0.6));
    //s.setKs(RGB(0,0,0));
    s.setKsp(RGB(0,0,0));
    s.setKr(RGB(0,0,0));
    s.setAlpha(15);
    r.addSphere(s);

    // Pelota espejo
    Vec center2(-5,-5,35,1);
    Vec normal7(0,6,0,0);
    Vec refCity2(-5,-5,32,1);
    Sphere s2(center2,normal7,refCity2);
    s2.setKd(RGB(0,0,0));
    s2.setKs(RGB(0,0,0));
    s2.setKsp(RGB(1,1,1));
    s2.setKr(RGB(0,0,0));
    s2.setAlpha(0);
    //r.addSphere(s2);

    // Pelota cristal
    Vec center3(10,0,25,1);
    Vec normal8(0,4,0,0);
    Vec refCity3(10,0,23,1);
    Sphere s3(center3,normal8,refCity3);
    s3.setKd(RGB(0,0,0));
    s3.setKs(RGB(0,0,0));
    s3.setKsp(RGB(0,0,0));
    s3.setKr(RGB(1,1,1));
    s3.setAlpha(0);
    //r.addSphere(s3);

    Vec origin6(-2.5,-10,44.8,1);
    Vec heigh(0,18,0,0);
    Vec wide(5,0,0,0);
    Square sq(origin6,wide,heigh,RGB(0,0,0));
    sq.setKd(RGB(0,0.3,0));
    sq.setKs(RGB(0,0,0));
    sq.setKsp(RGB(0,0,0));
    sq.setKr(RGB(0,0,0));
    sq.setAlpha(0);
    sq.addTextura("../negro.ppm");
    //r.addSquare(sq);

    // Luz
    //Light luz(100000000, Vec(10, 1, 15, POINT));
    Light luz(1000000, Vec(10, 4, 15, POINT));
    r.addLight(luz);

    r.trazar(numpaths);
    cout<<"acabo y escribo"<<endl;
    r.escribirImagen("nombre.ppm");
}

void pathTracerSquareTry(int numpaths){

    Vec l(-12.8,0,0,0);
    Vec u(0,7.2,0,0);
    Vec f(0,0,15,0);
    Vec o(0,0,0,1);
    Render r(720,1280,u,l,f,o);
    Vec origin1(0,0,45,1);
    Vec normal(0,0,-1,0);

    // Fondo
    Plane p(origin1,normal,RGB(0,0,0));
    p.setKd(RGB(0.8,0.8,0.8));
    p.setKs(RGB(0,0,0));
    p.setKsp(RGB(0,0,0));
    p.setKr(RGB(0,0,0));
    p.setAlpha(0);
    r.addPlane(p);

    //Square
    Vec origin2(-10,-10,44.95,1);
    Vec heigh(0,20,0,0);
    Vec wide(20,0,0,0);
    Square sq(origin2,wide,heigh,RGB(0,0,0));
    sq.setKd(RGB(0.3,0,0));
    sq.setKs(RGB(0,0,0));
    sq.setKsp(RGB(0,0,0));
    sq.setKr(RGB(0,0,0));
    sq.setAlpha(0);
    sq.addTextura("../Ventana.ppm");
    r.addSquare(sq);

    // Luz
    //Light luz(100000000, Vec(10, 1, 15, POINT));
    Light luz(1000000, Vec(10, 5, 15, POINT));
    //r.addLight(luz);

    r.trazar(numpaths);
    cout<<"acabo y escribo"<<endl;
    r.escribirImagen("nombre.ppm");
}

void pathTracerCornellBoxSummit(int numpaths){
    cout<<"Voy declarando"<<endl;
    Vec l(-12.8,0,0,0);
    Vec u(0,7.2,0,0);
    Vec f(0,0,15,0);
    Vec o(0,0,0,1);
    Render r(720,1280,u,l,f,o);
    Vec origin1(0,0,45,1);
    Vec normal(0,0,-1,0);
    // Fondo
    Plane p(origin1,normal,RGB(0,0,0));
    p.setKd(RGB(0.5,0.5,0.5));
    p.setKs(RGB(0,0,0));
    p.setKsp(RGB(0,0,0));
    p.setKr(RGB(0,0,0));
    p.setAlpha(0.2);
    r.addPlane(p);
    Vec origin2(0,-10,0,1);
    Vec normal2(0,1,0,0);
    // Suelo
    Plane q(origin2,normal2,RGB(0,0,0));
    q.setKd(RGB(0.5,0.5,0.5));
    q.setKs(RGB(0,0,0));
    q.setKsp(RGB(0,0,0));
    q.setKr(RGB(0,0,0));
    q.setAlpha(0.2);
    r.addPlane(q);
    Vec origin3(0,10,0,1);
    Vec normal3(0,-1,0,0);

    // Techo
    //Plane t(origin3,normal3,RGB(1000, 1000, 1000));
    Plane t(origin3,normal3,RGB(0, 0, 0));
    //Plane t(origin3,normal3,RGB(254, 254, 254));
    t.setKd(RGB(0.5,0.5,0.5));
    //t.setKd(RGB(0,0,0));
    t.setKs(RGB(0,0,0));
    t.setKsp(RGB(0,0,0));
    t.setKr(RGB(0,0,0));
    t.setAlpha(0.2);
    r.addPlane(t);
    // Plano izquierda
    Vec origin4(15,0,0,1);
    Vec normal4(-1,0,0,0);
    Plane v(origin4,normal4,RGB(0, 0,0));
    v.setKd(RGB(0.5,0.1,0.1));
    v.setKs(RGB(0,0,0));
    v.setKsp(RGB(0,0,0));
    v.setKr(RGB(0,0,0));
    v.setAlpha(0.2);
    r.addPlane(v);
    // Plano derecha
    Vec origin5(-15,0,0,1);
    Vec normal5(1,0,0,0);
    Plane w(origin5,normal5,RGB(0, 0,0));
    w.setKd(RGB(0.1,0.5,0.1));
    w.setKs(RGB(0,0,0));
    w.setKsp(RGB(0,0,0));
    w.setKr(RGB(0,0,0));
    w.setAlpha(0.2);
    r.addPlane(w);

    // Pelota Plastico
    Vec center(5,-6.95,27,1);
    Vec normal6(0,6,0,0);
    Vec refCity(5,-6.95,24,1);
    Sphere s(center,normal6,refCity);
    s.setKd(RGB(0.5,0.5,0));
    s.setKs(RGB(0.4,0.4,0));
    s.setKsp(RGB(0,0,0));
    s.setKr(RGB(0,0,0));
    s.setAlpha(20);
    r.addSphere(s);

    // Pelota medio espejo medio cristal
    Vec center2(-5,-6.95,32,1);
    Vec normal7(0,6,0,0);
    Vec refCity2(-5,-6.95,29,1);
    Sphere s2(center2,normal7,refCity2);
    s2.setKd(RGB(0,0,0));
    s2.setKs(RGB(0,0,0));
    s2.setKsp(RGB(0.4,0.4,0.4));
    s2.setKr(RGB(0.8,0.8,0.8));
    s2.setAlpha(0.02);
    r.addSphere(s2);

    Vec origin6(-10,-10,20,1);
    Vec heigh(0,0,20,0);
    Vec wide(20,0,0,0);
    Square sq(origin6,wide,heigh,RGB(0,0,0));
    sq.setKd(RGB(0.3,0,0));
    sq.setKs(RGB(0,0,0));
    sq.setKsp(RGB(0,0,0));
    sq.setKr(RGB(0,0,0));
    sq.setAlpha(0);
    sq.addTextura("../Ventana.ppm");
    r.addSquare(sq);

    // Luz
    //Light luz(100000000, Vec(10, 1, 15, POINT));
    Light luz(1000000, Vec(0, 7, 15, POINT));
    r.addLight(luz);

    cout<<"Comienzo a ejecutar"<<endl;
    r.trazar(numpaths);
    cout<<"acabo y escribo"<<endl;
    r.escribirImagen("nombre.ppm");
}

void pathTracerCornellBoxAreaSummit(int numpaths){
    Vec l(-12.8,0,0,0);
    Vec u(0,7.2,0,0);
    Vec f(0,0,15,0);
    Vec o(0,0,0,1);
    Render r(720,1280,u,l,f,o);
    Vec origin1(0,0,45,1);
    Vec normal(0,0,-1,0);
    // Fondo
    Plane p(origin1,normal,RGB(0,0,0));
    p.setKd(RGB(0.5,0.5,0.5));
    p.setKs(RGB(0,0,0));
    p.setKsp(RGB(0,0,0));
    p.setKr(RGB(0,0,0));
    p.setAlpha(0.2);
    r.addPlane(p);
    Vec origin2(0,-10,0,1);
    Vec normal2(0,1,0,0);
    // Suelo
    Plane q(origin2,normal2,RGB(0,0,0));
    q.setKd(RGB(0.5,0.5,0.5));
    q.setKs(RGB(0,0,0));
    q.setKsp(RGB(0,0,0));
    q.setKr(RGB(0,0,0));
    q.setAlpha(0.2);
    r.addPlane(q);
    Vec origin3(0,10,0,1);
    Vec normal3(0,-1,0,0);

    // Techo
    Plane t(origin3,normal3,RGB(1000, 1000, 1000));
    //Plane t(origin3,normal3,RGB(0, 0, 0));
    //Plane t(origin3,normal3,RGB(254, 254, 254));
    //t.setKd(RGB(0.5,0.5,0.5));
    t.setKd(RGB(0,0,0));
    t.setKs(RGB(0,0,0));
    t.setKsp(RGB(0,0,0));
    t.setKr(RGB(0,0,0));
    t.setAlpha(0.2);
    r.addPlane(t);
    // Plano izquierda
    Vec origin4(15,0,0,1);
    Vec normal4(-1,0,0,0);
    Plane v(origin4,normal4,RGB(0, 0,0));
    v.setKd(RGB(0.5,0.1,0.1));
    v.setKs(RGB(0,0,0));
    v.setKsp(RGB(0,0,0));
    v.setKr(RGB(0,0,0));
    v.setAlpha(0.2);
    r.addPlane(v);
    // Plano derecha
    Vec origin5(-15,0,0,1);
    Vec normal5(1,0,0,0);
    Plane w(origin5,normal5,RGB(0, 0,0));
    w.setKd(RGB(0.1,0.5,0.1));
    w.setKs(RGB(0,0,0));
    w.setKsp(RGB(0,0,0));
    w.setKr(RGB(0,0,0));
    w.setAlpha(0.2);
    r.addPlane(w);

    // Pelota Plastico
    Vec center(5,-6.95,27,1);
    Vec normal6(0,6,0,0);
    Vec refCity(5,-6.95,24,1);
    Sphere s(center,normal6,refCity);
    s.setKd(RGB(0.5,0.5,0));
    s.setKs(RGB(0.4,0.4,0));
    s.setKsp(RGB(0,0,0));
    s.setKr(RGB(0,0,0));
    s.setAlpha(20);
    r.addSphere(s);

    // Pelota medio espejo medio cristal
    Vec center2(-5,-6.95,32,1);
    Vec normal7(0,6,0,0);
    Vec refCity2(-5,-6.95,29,1);
    Sphere s2(center2,normal7,refCity2);
    s2.setKd(RGB(0,0,0));
    s2.setKs(RGB(0,0,0));
    s2.setKsp(RGB(0.4,0.4,0.4));
    s2.setKr(RGB(0.8,0.8,0.8));
    s2.setAlpha(0.02);
    r.addSphere(s2);

    Vec origin6(-10,-10,44.95,1);
    Vec heigh(0,20,0,0);
    Vec wide(20,0,0,0);
    Square sq(origin6,wide,heigh,RGB(0,0,0));
    sq.setKd(RGB(0.3,0,0));
    sq.setKs(RGB(0,0,0));
    sq.setKsp(RGB(0,0,0));
    sq.setKr(RGB(0,0,0));
    sq.setAlpha(0);
    sq.addTextura("../Ventana.ppm");
    r.addSquare(sq);

    // Luz
    //Light luz(100000000, Vec(10, 1, 15, POINT));
    Light luz(1000000, Vec(0, 7, 15, POINT));
    //r.addLight(luz);

    r.trazar(numpaths);
    cout<<"acabo y escribo"<<endl;
    r.escribirImagen("nombre.ppm");
}

void pathTracerCornellBoxAreaQuad(int numpaths){
    Vec l(-12.8,0,0,0);
    Vec u(0,7.2,0,0);
    Vec f(0,0,15,0);
    Vec o(0,0,0,1);
    Render r(720,1280,u,l,f,o);
    Vec origin1(0,0,45,1);
    Vec normal(0,0,-1,0);
    // Fondo
    Plane p(origin1,normal,RGB(0,0,0));
    p.setKd(RGB(0.5,0.5,0.5));
    p.setKs(RGB(0,0,0));
    p.setKsp(RGB(0,0,0));
    p.setKr(RGB(0,0,0));
    p.setAlpha(0.2);
    r.addPlane(p);
    Vec origin2(0,-10,0,1);
    Vec normal2(0,1,0,0);
    // Suelo
    Plane q(origin2,normal2,RGB(0,0,0));
    q.setKd(RGB(0.5,0.5,0.5));
    q.setKs(RGB(0,0,0));
    q.setKsp(RGB(0,0,0));
    q.setKr(RGB(0,0,0));
    q.setAlpha(0.2);
    r.addPlane(q);
    Vec origin3(0,10,0,1);
    Vec normal3(0,-1,0,0);

    // Techo
    //Plane t(origin3,normal3,RGB(1000, 1000, 1000));
    Plane t(origin3,normal3,RGB(0, 0, 0));
    //Plane t(origin3,normal3,RGB(254, 254, 254));
    t.setKd(RGB(0.5,0.5,0.5));
    //t.setKd(RGB(0,0,0));
    t.setKs(RGB(0,0,0));
    t.setKsp(RGB(0,0,0));
    t.setKr(RGB(0,0,0));
    t.setAlpha(0.2);
    r.addPlane(t);
    // Plano izquierda
    Vec origin4(15,0,0,1);
    Vec normal4(-1,0,0,0);
    Plane v(origin4,normal4,RGB(0, 0,0));
    v.setKd(RGB(0.5,0.1,0.1));
    v.setKs(RGB(0,0,0));
    v.setKsp(RGB(0,0,0));
    v.setKr(RGB(0,0,0));
    v.setAlpha(0.2);
    r.addPlane(v);
    // Plano derecha
    Vec origin5(-15,0,0,1);
    Vec normal5(1,0,0,0);
    Plane w(origin5,normal5,RGB(0, 0,0));
    w.setKd(RGB(0.1,0.5,0.1));
    w.setKs(RGB(0,0,0));
    w.setKsp(RGB(0,0,0));
    w.setKr(RGB(0,0,0));
    w.setAlpha(0.2);
    r.addPlane(w);

    // Pelota Plastico
    Vec center(5,-6.95,27,1);
    Vec normal6(0,6,0,0);
    Vec refCity(5,-6.95,24,1);
    Sphere s(center,normal6,refCity);
    s.setKd(RGB(0.5,0.5,0));
    s.setKs(RGB(0.4,0.4,0));
    s.setKsp(RGB(0,0,0));
    s.setKr(RGB(0,0,0));
    s.setAlpha(20);
    r.addSphere(s);

    // Pelota medio espejo medio cristal
    Vec center2(-5,-6.95,32,1);
    Vec normal7(0,6,0,0);
    Vec refCity2(-5,-6.95,29,1);
    Sphere s2(center2,normal7,refCity2);
    s2.setKd(RGB(0,0,0));
    s2.setKs(RGB(0,0,0));
    s2.setKsp(RGB(0.4,0.4,0.4));
    s2.setKr(RGB(0.8,0.8,0.8));
    s2.setAlpha(0.02);
    r.addSphere(s2);

    Vec origin6(3,9.95,30,1);
    Vec heigh(0,0,5,0);
    Vec wide(5,0,0,0);
    Square sq(origin6,wide,heigh,RGB(1000,1000,1000));
    sq.setKd(RGB(0.5,0,0));
    sq.setKs(RGB(0,0,0));
    sq.setKsp(RGB(0,0,0));
    sq.setKr(RGB(0,0,0));
    sq.setAlpha(0);
    r.addSquare(sq);

    // Luz
    //Light luz(100000000, Vec(10, 1, 15, POINT));
    Light luz(1000000, Vec(0, -7, 15, POINT));
    //r.addLight(luz);

    r.trazar(numpaths);
    cout<<"acabo y escribo"<<endl;
    r.escribirImagen("nombre.ppm");
}

void pathTracerColorBleeding(int numpaths){
    Vec l(-12.8,0,0,0);
    Vec u(0,7.2,0,0);
    Vec f(0,0,15,0);
    Vec o(0,0,0,1);
    Render r(720,1280,u,l,f,o);
    Vec origin1(0,0,45,1);
    Vec normal(0,0,-1,0);
    // Fondo
    Plane p(origin1,normal,RGB(0,0,0));
    p.setKd(RGB(0.5,0.5,0.5));
    p.setKs(RGB(0,0,0));
    p.setKsp(RGB(0,0,0));
    p.setKr(RGB(0,0,0));
    p.setAlpha(0.2);
    r.addPlane(p);
    Vec origin2(0,-10,0,1);
    Vec normal2(0,1,0,0);
    // Suelo
    Plane q(origin2,normal2,RGB(0,0,0));
    q.setKd(RGB(0.5,0.5,0.5));
    q.setKs(RGB(0,0,0));
    q.setKsp(RGB(0,0,0));
    q.setKr(RGB(0,0,0));
    q.setAlpha(0.2);
    r.addPlane(q);
    Vec origin3(0,10,0,1);
    Vec normal3(0,-1,0,0);

    // Techo
    //Plane t(origin3,normal3,RGB(1000, 1000, 1000));
    Plane t(origin3,normal3,RGB(0, 0, 0));
    //Plane t(origin3,normal3,RGB(254, 254, 254));
    t.setKd(RGB(0.5,0.5,0.5));
    //t.setKd(RGB(0,0,0));
    t.setKs(RGB(0,0,0));
    t.setKsp(RGB(0,0,0));
    t.setKr(RGB(0,0,0));
    t.setAlpha(0.2);
    r.addPlane(t);
    // Plano izquierda
    Vec origin4(15,0,0,1);
    Vec normal4(-1,0,0,0);
    Plane v(origin4,normal4,RGB(0, 0,0));
    v.setKd(RGB(0.8,0.1,0.1));
    v.setKs(RGB(0,0,0));
    v.setKsp(RGB(0,0,0));
    v.setKr(RGB(0,0,0));
    v.setAlpha(0.2);
    r.addPlane(v);
    // Plano derecha
    Vec origin5(-15,0,0,1);
    Vec normal5(1,0,0,0);
    Plane w(origin5,normal5,RGB(0, 0,0));
    w.setKd(RGB(0.1,0.8,0.1));
    w.setKs(RGB(0,0,0));
    w.setKsp(RGB(0,0,0));
    w.setKr(RGB(0,0,0));
    w.setAlpha(0.2);
    r.addPlane(w);

    // Pelota Plastico
    Vec center(10,-5,22,1);
    Vec normal6(0,6,0,0);
    Vec refCity(10,-5,19,1);
    Sphere s(center,normal6,refCity);
    s.setKd(RGB(0.5,0.5,0));
    s.setKs(RGB(0.3,0.3,0));
    s.setKsp(RGB(0,0,0));
    s.setKr(RGB(0,0,0));
    s.setAlpha(8);
    r.addSphere(s);

    // Luz
    //Light luz(100000000, Vec(10, 1, 15, POINT));
    Light luz(1000000, Vec(0, 7, 15, POINT));
    r.addLight(luz);

    r.trazar(numpaths);
    cout<<"acabo y escribo"<<endl;
    r.escribirImagen("nombre.ppm");
}

void pathTracerBillar(int numpaths){
    Vec l(-12.8,0,0,0);
    Vec u(0,7.2,0,0);
    Vec f(0,0,15,0);
    Vec o(0,0,0,1);
    Render r(720,1280,u,l,f,o);
    Vec origin1(0,0,1000,1);
    Vec normal(0,0,-1,0);
    // Fondo
    Plane p(origin1,normal,RGB(0,0,0));
    p.setKd(RGB(0.01,0.01,0.01));
    p.setKs(RGB(0,0,0));
    p.setKsp(RGB(0,0,0));
    p.setKr(RGB(0,0,0));
    p.setAlpha(0.2);
    r.addPlane(p);
    Vec origin2(0,-250,0,1);
    Vec normal2(0,1,0,0);
    // Suelo
    Plane q(origin2,normal2,RGB(0,0,0));
    q.setKd(RGB(0.01,0.01,0.01));
    q.setKs(RGB(0,0,0));
    q.setKsp(RGB(0,0,0));
    q.setKr(RGB(0,0,0));
    q.setAlpha(0.2);
    r.addPlane(q);
    Vec origin3(0,250,0,1);
    Vec normal3(0,-1,0,0);

    // Techo
    //Plane t(origin3,normal3,RGB(1000, 1000, 1000));
    Plane t(origin3,normal3,RGB(0, 0, 0));
    //Plane t(origin3,normal3,RGB(254, 254, 254));
    //t.setKd(RGB(0.5,0.5,0.5));
    t.setKd(RGB(0.01,0.01,0.01));
    t.setKs(RGB(0,0,0));
    t.setKsp(RGB(0,0,0));
    t.setKr(RGB(0,0,0));
    t.setAlpha(0.2);
    r.addPlane(t);
    // Plano izquierda
    Vec origin4(375,0,0,1);
    Vec normal4(-1,0,0,0);
    Plane v(origin4,normal4,RGB(0, 0,0));
    v.setKd(RGB(0.01,0.01,0.01));
    v.setKs(RGB(0,0,0));
    v.setKsp(RGB(0,0,0));
    v.setKr(RGB(0,0,0));
    v.setAlpha(0.2);
    r.addPlane(v);
    // Plano derecha
    Vec origin5(-375,0,0,1);
    Vec normal5(1,0,0,0);
    Plane w(origin5,normal5,RGB(0, 0,0));
    w.setKd(RGB(0.01,0.01,0.01));
    w.setKs(RGB(0,0,0));
    w.setKsp(RGB(0,0,0));
    w.setKr(RGB(0,0,0));
    w.setAlpha(0.2);
    r.addPlane(w);

    RGB color = RGB(0.2,0.4,0.2);
    //Suelo mesa
    Vec origin6(-20,-17,45,1);
    Vec heigh(0,0,80,0);
    Vec wide(40,0,0,0);
    Square sq(origin6,wide,heigh,RGB(0,0,0));
    sq.setKd(color);
    sq.setKs(RGB(0,0,0));
    sq.setKsp(RGB(0,0,0));
    sq.setKr(RGB(0,0,0));
    sq.setAlpha(0);
    r.addSquare(sq);

    //pared frente
    Vec origin9(-23,-17,44.9,1);
    heigh = Vec(0,3,0,0);
    wide = Vec(46,0,0,0);
    Square sq3(origin9,wide,heigh,RGB(0,0,0));
    sq3.setKd(color);
    sq3.setKs(RGB(0,0,0));
    sq3.setKsp(RGB(0,0,0));
    sq3.setKr(RGB(0,0,0));
    sq3.setAlpha(0);
    r.addSquare(sq3);

    //techo frente
    Vec origin11(-23,-13.9,44.8999,1);
    heigh=Vec(0,0,3,0);
    wide=Vec(46,0,0,0);
    Square sq5(origin11,wide,heigh,RGB(0,0,0));
    sq5.setKd(color);
    sq5.setKs(RGB(0,0,0));
    sq5.setKsp(RGB(0,0,0));
    sq5.setKr(RGB(0,0,0));
    sq5.setAlpha(0);
    r.addSquare(sq5);

    //pared fondo
    Vec origin10(-23,-17,125.1,1);
    heigh = Vec(0,3,0,0);
    wide = Vec(46,0,0,0);
    Square sq4(origin10,wide,heigh,RGB(0,0,0));
    sq4.setKd(color);
    sq4.setKs(RGB(0,0,0));
    sq4.setKsp(RGB(0,0,0));
    sq4.setKr(RGB(0,0,0));
    sq4.setAlpha(0);
    r.addSquare(sq4);

    //techo fondo
    Vec origin12(-23,-13.9,125.2,1);
    heigh=Vec(0,0,3,0);
    wide=Vec(46,0,0,0);
    Square sq6(origin12,wide,heigh,RGB(0,0,0));
    sq6.setKd(color);
    sq6.setKs(RGB(0,0,0));
    sq6.setKsp(RGB(0,0,0));
    sq6.setKr(RGB(0,0,0));
    sq6.setAlpha(0);
    r.addSquare(sq6);

    //pared derecha
    Vec origin7(-20.01,-16.9,48,1);
    heigh = Vec(0,3,0,0);
    wide = Vec(0,0,77,0);
    Square sq1(origin7,wide,heigh,RGB(0,0,0));
    sq1.setKd(color);
    sq1.setKs(RGB(0,0,0));
    sq1.setKsp(RGB(0,0,0));
    sq1.setKr(RGB(0,0,0));
    sq1.setAlpha(0);
    r.addSquare(sq1);

    //techo derecha
    Vec origin13(-23,-13.99,47,1);
    heigh=Vec(0,0,77,0);
    wide=Vec(3,0,0,0);
    Square sq8(origin13,wide,heigh,RGB(0,0,0));
    sq8.setKd(color);
    sq8.setKs(RGB(0,0,0));
    sq8.setKsp(RGB(0,0,0));
    sq8.setKr(RGB(0,0,0));
    sq8.setAlpha(0);
    r.addSquare(sq8);

    //pared izquierda
    Vec origin8(20.01,-13.99,122,1);
    heigh = Vec(0,-3,0,0);
    wide = Vec(0,0,77,0);
    Square sq2(origin8,wide,heigh,RGB(0,0,0));
    sq2.setKd(color);
    sq2.setKs(RGB(0,0,0));
    sq2.setKsp(RGB(0,0,0));
    sq2.setKr(RGB(0,0,0));
    sq2.setAlpha(0);
    r.addSquare(sq2);

    //techo izquierda
    Vec origin14(20,-13.99,47,1);
    heigh=Vec(0,0,77,0);
    wide=Vec(3,0,0,0);
    Square sq9(origin14,wide,heigh,RGB(0,0,0));
    sq9.setKd(color);
    sq9.setKs(RGB(0,0,0));
    sq9.setKsp(RGB(0,0,0));
    sq9.setKr(RGB(0,0,0));
    sq9.setAlpha(0);
    r.addSquare(sq9);

    // Pelota Plastico
    Vec center(0,-15.39,68,1);
    Vec normal6(0,3,0,0);
    Vec refCity(0,-15.39,66.5,1);
    Sphere s(center,normal6,refCity);
    s.setKd(RGB(0.9,0.9,0.9));
    s.setKs(RGB(0.3,0.3,0.3));
    s.setKsp(RGB(0,0,0));
    s.setKr(RGB(0,0,0));
    s.setAlpha(8);
    r.addSphere(s);

    // Pelota Plastico
    Vec center2(5,-15.39,90,1);
    Vec refCity2(5,-15.39,88.5,1);
    Sphere s2(center2,normal6,refCity2);
    s2.setKd(RGB(0.8,0.5,0));
    s2.setKs(RGB(0.6,0.3,0));
    s2.setKsp(RGB(0,0,0));
    s2.setKr(RGB(0,0,0));
    s2.setAlpha(8);
    r.addSphere(s2);

    // Pelota Plastico
    Vec center7(-10,-15.39,115,1);
    Vec refCity3(-10,-15.39,113.5,1);
    Sphere s3(center7,normal6,refCity3);
    s3.setKd(RGB(0.3,0,0.3));
    s3.setKs(RGB(0.1,0,0.1));
    s3.setKsp(RGB(0,0,0));
    s3.setKr(RGB(0,0,0));
    s3.setAlpha(8);
    r.addSphere(s3);

    // Pelota Plastico
    Vec center8(13,-15.39,100,1);
    Vec refCity4(13,-15.39,98.5,1);
    Sphere s4(center8,normal6,refCity4);
    s4.setKd(RGB(0.8,0.8,0));
    s4.setKs(RGB(0.4,0.4,0));
    s4.setKsp(RGB(0,0,0));
    s4.setKr(RGB(0,0,0));
    s4.setAlpha(8);
    r.addSphere(s4);

    // Luz
    //Light luz(100000000, Vec(10, 1, 15, POINT));
    Light luz(1000000, Vec(0, 20, 20, POINT));
    r.addLight(luz);

    r.trazar(numpaths);
    cout<<"acabo y escribo"<<endl;
    r.escribirImagen("nombre.ppm");
}

void bolos(int numpaths){
    Vec l(-12.8,0,0,0);
    Vec u(0,7.2,0,0);
    Vec f(0,0,15,0);
    Vec o(0,0,0,1);
    Render r(720,1280,u,l,f,o);
    Vec origin1(0,0,45,1);
    Vec normal(0,0,-1,0);
    // Fondo
    Plane p(origin1,normal,RGB(0,0,0));
    p.setKd(RGB(0.5,0.5,0.5));
    p.setKs(RGB(0,0,0));
    p.setKsp(RGB(0,0,0));
    p.setKr(RGB(0,0,0));
    p.setAlpha(0.2);
    r.addPlane(p);
    Vec origin2(0,-10,0,1);
    Vec normal2(0,1,0,0);
    // Suelo
    Plane q(origin2,normal2,RGB(0,0,0));
    q.setKd(RGB(0.5,0.5,0.5));
    q.setKs(RGB(0,0,0));
    q.setKsp(RGB(0,0,0));
    q.setKr(RGB(0,0,0));
    q.setAlpha(0.2);
    r.addPlane(q);
    Vec origin3(0,40,0,1);
    Vec normal3(0,-1,0,0);

    // Techo
    Plane t(origin3,normal3,RGB(1000, 1000, 1000));
    //Plane t(origin3,normal3,RGB(0, 0, 0));
    //Plane t(origin3,normal3,RGB(254, 254, 254));
    //t.setKd(RGB(0.5,0.5,0.5));
    t.setKd(RGB(0,0,0));
    t.setKs(RGB(0,0,0));
    t.setKsp(RGB(0,0,0));
    t.setKr(RGB(0,0,0));
    t.setAlpha(0.2);
    r.addPlane(t);
    // Plano izquierda
    Vec origin4(80,0,0,1);
    Vec normal4(-1,0,0,0);
    Plane v(origin4,normal4,RGB(0, 0,0));
    v.setKd(RGB(0.5,0.1,0.1));
    v.setKs(RGB(0,0,0));
    v.setKsp(RGB(0,0,0));
    v.setKr(RGB(0,0,0));
    v.setAlpha(0.2);
    r.addPlane(v);
    // Plano derecha
    Vec origin5(-80,0,0,1);
    Vec normal5(1,0,0,0);
    Plane w(origin5,normal5,RGB(0, 0,0));
    w.setKd(RGB(0.1,0.5,0.1));
    w.setKs(RGB(0,0,0));
    w.setKsp(RGB(0,0,0));
    w.setKr(RGB(0,0,0));
    w.setAlpha(0.2);
    r.addPlane(w);

    // Pelota Plastico
    Vec center(0,-6.95,27,1);
    Vec normal6(0,6,0,0);
    Vec refCity(0,-6.95,24,1);
    Sphere s(center,normal6,refCity);
    s.setKd(RGB(0.5,0.5,0.5));
    s.setKs(RGB(0.4,0.4,0.4));
    s.setKsp(RGB(0,0,0));
    s.setKr(RGB(0,0,0));
    s.setAlpha(0.02);
    r.addSphere(s);

    // Pelota arriba
    Vec center1(0,-1.9,27,1);
    Vec normal7(0,4,0,0);
    Vec refCity2(0,-1.9,25,1);
    Sphere s2(center1,normal7,refCity2);
    s2.setKd(RGB(0.5,0.5,0.5));
    s2.setKs(RGB(0.4,0.4,0.4));
    s2.setKsp(RGB(0,0,0));
    s2.setKr(RGB(0,0,0));
    s2.setAlpha(0.02);
    r.addSphere(s2);

    // Ojo derecho
    Vec center3(-0.75,-1.5,25,1);
    Vec normal8(0,0.5,0,0);
    Vec refCity3(-0.75,-1.5,24.75,1);
    Sphere s3(center3,normal8,refCity3);
    s3.setKd(RGB(0.01,0.01,0.01));
    s3.setKs(RGB(0.01,0.01,0.01));
    s3.setKsp(RGB(0,0,0));
    s3.setKr(RGB(0,0,0));
    s3.setAlpha(0);
    r.addSphere(s3);

    // Ojo izquierdo
    Vec center4(0.75,-1.5,25,1);
    Vec normal9(0,0.5,0,0);
    Vec refCity4(0.75,-1.5,24.75,1);
    Sphere s4(center4,normal9,refCity4);
    s4.setKd(RGB(0.01,0.01,0.01));
    s4.setKs(RGB(0.01,0.01,0.01));
    s4.setKsp(RGB(0,0,0));
    s4.setKr(RGB(0,0,0));
    s4.setAlpha(0);
    r.addSphere(s4);

    // Nariz
    Vec center5(0,-2.25,25,1);
    Vec normal10(0,0.5,0,0);
    Vec refCity5(0,-2.25,24.75,1);
    Sphere s5(center5,normal10,refCity5);
    s5.setKd(RGB(0.6,0.3,0.1));
    s5.setKs(RGB(0.6,0.3,0.1));
    s5.setKsp(RGB(0,0,0));
    s5.setKr(RGB(0,0,0));
    s5.setAlpha(0);
    r.addSphere(s5);

    // Boton 1
    Vec center6(0,-4.5,23.5,1);
    Vec refCity6(0,-4.5,23.25,1);
    Sphere s6(center6,normal10,refCity6);
    s6.setKd(RGB(0.01,0.01,0.01));
    s6.setKs(RGB(0.01,0.01,0.01));
    s6.setKsp(RGB(0,0,0));
    s6.setKr(RGB(0,0,0));
    s6.setAlpha(0);
    r.addSphere(s6);

    // Boton 1
    Vec center7(0,-6,23.5,1);
    Vec refCity7(0,-6,23.25,1);
    Sphere s7(center7,normal10,refCity7);
    s7.setKd(RGB(0.01,0.01,0.01));
    s7.setKs(RGB(0.01,0.01,0.01));
    s7.setKsp(RGB(0,0,0));
    s7.setKr(RGB(0,0,0));
    s7.setAlpha(0);
    r.addSphere(s7);

    // Boton 1
    Vec center8(0,-8,23.5,1);
    Vec refCity8(0,-8,23.25,1);
    Sphere s8(center8,normal10,refCity8);
    s8.setKd(RGB(0.01,0.01,0.01));
    s8.setKs(RGB(0.01,0.01,0.01));
    s8.setKsp(RGB(0,0,0));
    s8.setKr(RGB(0,0,0));
    s8.setAlpha(0);
    r.addSphere(s8);

    Vec origin6(-39,-10,20,1);
    Vec heigh(0,0,44,0);
    Vec wide(80,0,0,0);
    Square sq(origin6,wide,heigh,RGB(0,0,0));
    sq.setKd(RGB(0.3,0,0));
    sq.setKs(RGB(0,0,0));
    sq.setKsp(RGB(0,0,0));
    sq.setKr(RGB(0,0,0));
    sq.setAlpha(0);
    sq.addTextura("../nieve.ppm");
    r.addSquare(sq);

    Vec origin10(-40,-10,44.95,1);
    heigh = Vec(0,50,0,0);
    wide = Vec(80,0,0,0);
    Square sq2(origin10,wide,heigh,RGB(0,0,0));
    sq2.setKd(RGB(0.3,0,0));
    sq2.setKs(RGB(0,0,0));
    sq2.setKsp(RGB(0,0,0));
    sq2.setKr(RGB(0,0,0));
    sq2.setAlpha(0);
    sq2.addTextura("../bosque.ppm");
    r.addSquare(sq2);

    // Luz
    //Light luz(100000000, Vec(10, 1, 15, POINT));
    Light luz(1000000, Vec(0, 7, 15, POINT));
    //r.addLight(luz);

    r.trazar(numpaths);
    cout<<"acabo y escribo"<<endl;
    r.escribirImagen("nombre.ppm");
}

int main( int argc, char * argv[] )
{
    int numpaths;
    if(argc == 2){
        numpaths = stoi(argv[1]);
    }
    else{
        numpaths = 10;
    }
    unsigned t0, t1;
    t0=clock();
    //pathTracerCornellBox1(numpaths);
    //pathTracerSquareTry(numpaths);
    //pathTracerCornellBoxSummit(numpaths);
    //pathTracerCornellBoxAreaSummit(numpaths);
    //pathTracerCornellBoxAreaQuad(numpaths);
    // pathTracerColorBleeding(numpaths);
    //pathTracerBillar(numpaths);
    bolos(numpaths);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    int min = time/60;
    int seg = time;
    int mil = (time-seg)*1000;
    seg = seg % 60;
    cout << "Execution Time: ";
    if(min!=0){
        cout << min << " minutes ";
    }
    cout << seg << " seconds and " << mil << " miliseconds." << endl;
    return 0;
}