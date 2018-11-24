//
// Created by Nicolas on 02/11/2018.
//

#ifndef COMPUTER_GRAPHICS_RENDER_H
#define COMPUTER_GRAPHICS_RENDER_H

#include <fstream>
#include "../imaging/RGB.h"
#include "Plane.h"
#include "Sphere.h"
#include "../imaging/Image.h"
#include "Object.h"
#include <random>
#include <iostream>
#include <stdlib.h>


using namespace std;

class Render{

public:

    Render(const Vec &u, const Vec &l, const Vec &f, const Vec &o) : u(u), l(l), f(f), o(o) {
        this->numSpheres = 0;
        this->numPlanos = 0;
        RGB negro(0,0,0);
        for (int i = 0; i < 144; i++){
            for (int j = 0; j < 256; j++){
                img[i][j] = negro;
            }
        }
        ReferenceSystem UCS(u,l,f,o);
        this->UCS = UCS;
    }

    Render() {}

    void addPlane(Plane p){
        this->ps[numPlanos]=p;
        this->numPlanos++;
    }

    void addSphere(Sphere s){
        this->spheres[numSpheres]=s;
        this->numSpheres++;
    }

    void trazar(){
        int uMod = u.modulus();
        int lMod = l.modulus();
        u.getUnitVector();
        l.getUnitVector();
        for(int i=uMod;i>-uMod;i--){
            for(int j=-lMod;j<lMod;j++){
                Vec pixel = f + (i-0.5)*u + (j+0.5) * l;
                pixel.setType(1);
                RGB x = pixelColor(pixel);
                if ((uMod-i)==130 && (lMod+j) == 80){
                    cout << "debug" << endl;
                }
                img[uMod-i][lMod+j]= x;
            }
            cout << "Llevo " << i << " de " << -uMod<<endl;
        }
        cout << "ACABO" << endl;
        u=u*uMod;
        l=l*lMod;
    }

    void escribirImagen(string path){
        ofstream file;
        file.open(path);
        file << "P3" << endl;
        file << "#MAX=1000000" << endl;
        file << "# mpi_atrium_3.ppm" << endl;
        file << "256 144" << endl;
        file << "10000000" << endl;

        float coefficient = 1;//65535/255;
        for (int i = 0; i < 144; i++){
            for (int j = 0; j < 256; j++){
                int R, G, B;
                R = max(img[i][j].getR() * coefficient,0);
                G = max(img[i][j].getG() * coefficient,0);
                B = max(img[i][j].getB() * coefficient,0);
                file << R << " " << G << " " << B << "   ";
            }
            file << '\n';
            if(i%20==0&&i!=0) {
                cout << "20 filas escritas" << endl;
            }
        }
        cout<<"final"<<endl;
        file.close();
        Image image(path);
        //image.gammaCurve(2.2);
        image.equalization();
        image.writeImage();
    }

    const Vec &getU() const {
        return u;
    }

    void setU(const Vec &u) {
        Render::u = u;
    }

    const Vec &getL() const {
        return l;
    }

    void setL(const Vec &l) {
        Render::l = l;
    }

    const Vec &getF() const {
        return f;
    }

    void setF(const Vec &f) {
        Render::f = f;
    }

    const Vec &getO() const {
        return o;
    }

    void setO(const Vec &o) {
        Render::o = o;
    }

private:

    RGB pixelColor(Vec pixel){
        //cout << pixel.getX() << " - "<< pixel.getY() << endl;
        Vec v = pixel-o;
        float minMod=-1;
        RGB color(0,0,0);
        Vec ptoHit;
        Plane planeHit;
        bool hit=false;
        // Debug
        if(pixel.getY() > -50 && pixel.getY() < -52 ){
            //cout << "Debug pixel" << endl;
        }
        for(int i=0;i<numPlanos;++i){
            Plane p = ps[i];
            Vec point;
            if(p.intercepts(pixel,v,point,UCS)){
                hit=true;
                //cout<<"Intercepta  -->  " << i << endl;
                Vec vp = point - pixel;
                float distance = vp.modulus();
                if(minMod==-1||minMod>distance){
                    minMod=vp.modulus();
                    planeHit = p;
                    ptoHit = point;
                    // vp es el rayo
                    // pixel es el punto de interseccion
                    //color = renderEquation(pixel, vp, p);
                    //color = p.getProps();
                }
            }
        }
        int numPaths = 1;
        for (int j = 0; j < numPaths; j++){
           color = color + renderEquation(ptoHit,v,planeHit);
        }
        color = color / numPaths;
        for(int i=0;i<numSpheres;i++){
            Sphere s = spheres[i];
            Vec point;
            if(s.intercepts(pixel,v,point)){
                hit=true;
                //cout<<"Intercepta esferita papa" <<endl;
                //cout << point.getX() << "-" << point.getY() << "-" << point.getZ() << endl;
                Vec vp = point - pixel;
                if(minMod==-1||minMod>vp.modulus()){
                    minMod=vp.modulus();
                    color = s.getProps();
                }
            }
        }
        return color;
    }

    static float max(float a, float b){
        if(a > b){
            return a;
        }
        else{
            return b;
        }
    }

    // x -> punto de interseccion
    // wo -> recta que ha intersectado
    // o -> objeto con el que ha intersectado
    // HACERLO EN COORDENADAS LOCALES
    RGB renderEquation(Vec x, Vec wo, Plane p){
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<float> dist(0.0, 1.0);
        RGB color(0, 0, 0);
        RGB acumulado(1.0, 1.0, 1.0);
        bool absorcion = false;
        bool interseccion = true;
        bool emitter = false;

        if (p.getKd().getB()>0.8){
           cout<<"choco azul"<<endl;
        }
        if (p.getKd().getR()>0.8){
            //cout<<"choco rojo"<<endl;
        }
        else if(p.getProps().getB() > 0){
        //    cout << "choco emisor" << endl;
        }
        while (!absorcion && interseccion && !emitter){
            // Sistema de coordenadas local respecto del punto x en el objeto o
            ReferenceSystem local = p.createReferenceSystemLocal(x);
            Matrix referenceSystem = local.getMatrix().inverse();
            x = referenceSystem*x;

            // Tiro ruleta rusa
            // https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
            float rr = randZeroToOne();//dist(mt);

            if(p.isEmitter()){
                color = color + acumulado * p.getProps();
                emitter = true;
            }

            // TODO sacar los valores
            float kd, ks, ksp, kr;
            kd = 0.3;
            ks = 0.5;

            // TODO normalizar entre 0 y 0.9

            if (rr < kd + ks){
                // TODO phong
                // TODO acumular angulo de incidencia
                acumulado = acumulado * (p.getKd() / M_PI);
                // TODO dividir para el anguludo de incidencia con la probabilidad esa
                // acumulado = acumulado / ((kd + ks)*)

                // Muestrear rayo uniform cosine sampling
                float randNum = randZeroToOne();//dist(mt);
                float theta = acos(sqrt(1-randNum));
                float phi = 2 * M_PI * randNum;

                // Sphere coordenates -> cartesian
                float i = sin(theta)*cos(phi);
                float j = sin(theta)*sin(phi);
                float k = cos(theta);

                Vec randPoint(i,j,k,POINT);
                // To local coordinates
                randPoint = referenceSystem*randPoint;
                wo = randPoint - x;

                // To global coordinates
                wo = local.getMatrix()*wo;
                x = local.getMatrix()*x;


                // TODO itercepts true or false
                interseccion = nearestIntersection(wo, x, p, wo, p, local);


            }
            else{ // rr indica absorcion
                absorcion = true;
            }
        }

        return color;



    }

    // v -> rayo
    // x -> origen del rayo
    bool nearestIntersection(Vec v, Vec x, Plane myPlane, Vec& ptoHit, Plane& planeHit, ReferenceSystem r){
        float minMod=-1;
        RGB color(0,0,0);
        bool hit=false;
        for(int i=0;i<numPlanos;++i){
            Plane p = ps[i];
            if (p != myPlane){
                Vec point;
                if(p.intercepts(x,v,point,r)){
                    hit=true;
                    Vec vp = point - x;
                    if(minMod==-1||minMod>vp.modulus()){
                        minMod=vp.modulus();
                        ptoHit = point;
                        planeHit = p;
                    }
                }
            }

        }
        return hit;
    }

    // El centro de local es el punto de intersección
    float calculateDirectLight(ReferenceSystem local){
        Matrix referenceSystem = local.getMatrix().inverse();
        //referenceSystem = local.getMatrix();
        Vec x = referenceSystem*local.getOrigin();
        //x = local.getOrigin();
        float totalLight = 0;
        Vec light(1, 1, 1, 1);
        Vec lightLocal = referenceSystem*light;
        //lightLocal = light;
        for (int i = 0; i < 1; i++){
            //TODO  Por cada geometría comprobar si intercepta o no, sino es sombra

            Vec rayo = lightLocal - x;
            // ¿Luz me viene de espaldas?
            if (rayo.getZ()>=0) {
                // p / |c-x|^2
                totalLight += 1000000 / (pow((rayo).modulus(),2));
            }
            //else{
          //      cout<<"kk"<<endl;
            //}
        }
        return totalLight;
    }

   // RGB brdf(Vec x, Vec wi, Vec w0, Plane p){
    //    return lambertian(p.getProps()) + phong(x, wi, w0);
    //}

    RGB lambertian(RGB kd){
        return kd / M_PI;
    }

    RGB phong(Vec x, Vec wi, Vec w0, Plane p){
        RGB alpha = p.getAlpha();
        // return ((alpha + 2) / (2 * M_PI))*;
        return alpha;
    }

    float randZeroToOne()
    {
        return rand() / (RAND_MAX + 1.);
    }

    Vec u,l,f;
    Vec o;
    ReferenceSystem UCS;
    Plane ps[200];
    Sphere spheres[200];
    float lights[10];
    RGB img[144][256];
    int numPlanos;
    int numSpheres;
    int numLigthts;
};

#endif //COMPUTER_GRAPHICS_RENDER_H
