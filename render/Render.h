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
#include "RandomNumber.h"
#include "Light.h"


using namespace std;

class Render{

public:

    Render(const int x, const int y, const Vec &u, const Vec &l, const Vec &f, const Vec &o) : u(u), l(l), f(f), o(o) {
        this->numSpheres = 0;
        this->numPlanos = 0;
        this->numLights = 0;
        this->x=x;
        this->y=y;
        RGB negro(0,0,0);
        img = new RGB[x*y];
        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
                this->setPixel(i,j,negro);
            }
        }
        ReferenceSystem UCS(u,l,f,o);
        this->UCS = UCS;
        this->r = RandomNumber();
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

    void addLight(Light l){
        this->lights[numLights]=l;
        this->numLights++;
    }

    void trazar(){
        int uMod = u.modulus();
        int lMod = l.modulus();
        u.getUnitVector();
        l.getUnitVector();
        RandomNumber rn(0.001,0.199);
        Vec pixel;
        double restI,sumJ;
        int numPaths = 8; // NUMBER OF RAYS PER PIXEL
        for(double i=uMod;i>-uMod;i=i-0.2){
            for(double j=-lMod;j<lMod;j=j+0.2){
                RGB x(0,0,0);
               // cout << i << "->" << j << endl;
                for (int k = 0; k < numPaths; k++) {
                    if(i==-3 && j==-4){
                        cout << "x";
                    }
                    restI = rn.giveNumber();
                    sumJ = rn.giveNumber();
                    pixel = f + (i - restI) * u + (j + sumJ) * l;
                    pixel.setType(1);
                    x = x + pixelColor(pixel);
                }
                x = x / numPaths;
                this->setPixel((uMod-i)*5,(lMod+j)*5,x);
            }
            cout << "Escribo " << (uMod-i)*5 << " de " << uMod * 10 <<endl;
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
        file << "1280 720" << endl;
        file << "10000000" << endl;

        float coefficient = 1;//65535/255;
        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
                int R, G, B;
                if(i==73&&j==54){
                    cout<<"PASA"<<endl;
                }
                RGB aux = this->getPixel(i,j);
                R = max(aux.getR() * coefficient,0);
                G = max(aux.getG() * coefficient,0);
                B = max(aux.getB() * coefficient,0);
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
        image.gammaCurve(2.2);
        //image.equalization();
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
        Sphere sphereHit;
        bool hit=false;
        bool hitEsfera = false;
        Plane p;
        Vec point,vp;
        float distance;
        for(int i=0;i<numPlanos;++i){
            p = ps[i];
            if(p.intercepts(pixel,v,point)){
                hit=true;
                //cout<<"Intercepta  -->  " << i << endl;
                vp = point - pixel;
                distance = vp.modulus();
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
        for(int i=0;i<numSpheres;i++){
            Sphere s = spheres[i];
            if(s.intercepts(pixel,v,point)){
                hit=true;
                //cout<<"Intercepta esferita papa" <<endl;
                //cout << point.getX() << "-" << point.getY() << "-" << point.getZ() << endl;
                vp = point - pixel;
                if(minMod==-1||minMod>vp.modulus()){
                    minMod=vp.modulus();
                    color = s.getProps();
                    sphereHit = s;
                    ptoHit = point;
                    hitEsfera = true;
                }
            }
        }
        if(hitEsfera){
            Vec normal = ptoHit - sphereHit.getCenter();
            normal.getUnitVector();
            planeHit = Plane(ptoHit,normal,sphereHit.getProps());
            planeHit.setKs(sphereHit.getKs());
            planeHit.setKd(sphereHit.getKd());
            planeHit.setAlpha(sphereHit.getAlpha());
        }
        if(hit) {
            color = renderEquation(ptoHit, v, planeHit);
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
        RGB color(1, 1, 1);
        RGB acumulado(1.0, 1.0, 1.0);
        bool absorcion = false;
        bool interseccion = true;
        bool emitter = false;

        if (p.getKd().getB()>0.8){
           //cout<<"choco azul"<<endl;
        }
        if (p.getKd().getR()>0.8){
            //cout<<"choco rojo"<<endl;
        }
        else if(p.getProps().getB() > 0){
        //    cout << "choco emisor" << endl;
        }
        ReferenceSystem local;
        Matrix referenceSystem;
        float rr;
        float kd, ks, ksp, kr;
        float randNum,theta,phi,i,j,k;
        Vec wi;
        Vec wiDirecta;
        Vec xViejo;
        while (!absorcion && interseccion && !emitter){
            // Sistema de coordenadas local respecto del punto x en el objeto o
            local = p.createReferenceSystemLocal(x);
            referenceSystem = local.getMatrix().inverse();
            x = referenceSystem*x;
            wo.getUnitVector();

            if(p.isEmitter()){
                color = color + acumulado * p.getProps();
                emitter = true;
            }

            for(int i=0;i<numLights;++i){
                wiDirecta = lights[i].getPosition()-local.getOrigin();
                wiDirecta.getUnitVector();
                RGB phong = phongBRDF(p.getKd(),p.getKs(),p.getAlpha(),wiDirecta, local.getK());
                RGB directLightVal = directLight(local, p,lights[i]);
                color = color + acumulado * phong * directLightVal;
            }

            // TODO sacar los valores
            kd = 0.3;
            ks = 0.5;

            // TODO normalizar entre 0 y 0.9


            // Tiro ruleta rusa
            // https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
            rr = randZeroToOne();//dist(mt);

            if (rr < kd + ks){

                // Muestrear rayo uniform cosine sampling
                randNum = randZeroToOne();//dist(mt);
                theta = acos(sqrt(1-randNum));
                randNum = randZeroToOne();
                phi = 2 * M_PI * randNum;

                // Sphere coordenates -> cartesian
                i = sin(theta)*cos(phi);
                j = sin(theta)*sin(phi);
                k = cos(theta);

                Vec randPoint(i,j,k,POINT);
                // To local coordinates
                //randPoint = referenceSystem*randPoint;
                wi = randPoint - Vec(0, 0, 0, POINT);
                wi.getUnitVector();

                // To global coordinates
                // TODO no estoy seguro de wo
                wi = local.getMatrix()*wi;
                x = local.getMatrix()*x;

                // Luz directa
                //color = color + (p.getKd() / M_PI)*directLight(local, p);
                // TODO phong
                // TODO acumular angulo de incidencia
                acumulado = acumulado * phongBRDF(p.getKd(),p.getKs(),p.getAlpha(),wo, wi) / (2 * M_PI); // Se divide para la pdf
                // TODO dividir para el anguludo de incidencia con la probabilidad esa
                // acumulado = acumulado / ((kd + ks)*)

                //wo = Vec(1, -1, -1, DIRECTION);
                xViejo = x;
                interseccion = nearestIntersection(wi, x, p, x, p, local);

                wo = x - xViejo;
            }
            else{ // rr indica absorcion
                absorcion = true;
            }
        }

        return color;



    }

    RGB phongBRDF(RGB kd, RGB ks,float alpha, Vec wo, Vec wi){
        float aux = pow(abs(wo*wi),alpha);
        RGB part1 = kd / M_PI + ks * (alpha + 2)/(2*M_PI) * RGB(aux,aux,aux);
        return part1;
    }

    // v -> rayo
    // x -> origen del rayo
    bool nearestIntersection(Vec v, Vec x, Plane myPlane, Vec& ptoHit, Plane& planeHit, ReferenceSystem r){
        float minMod=-1;
        RGB color(0,0,0);
        bool hit=false;
        Vec point;
        Vec vp;
        Plane p;
        Sphere s,aux;
        bool hitSphere = false;
        for(int i=0;i<numPlanos;++i){
            p = ps[i];
            if (p != myPlane){
                if(p.intercepts(x,v,point)){
                    hit=true;
                    vp = point - x;
                    if(minMod==-1||minMod>vp.modulus()){
                        minMod=vp.modulus();
                        ptoHit = point;
                        planeHit = p;
                    }
                }
            }
        }
        for(int i=0;i<numSpheres;++i){
            s = spheres[i];
            if (!s.contains(p.getOrigin())){
                if(s.intercepts(x,v,point)){
                    vp = point - x;
                    if(!abs(vp.modulus())<0.1){
                        hit = true;
                        if (minMod == -1 || minMod > vp.modulus()) {
                            minMod = vp.modulus();
                            ptoHit = point;
                            aux = s;
                            hitSphere = true;
                        }
                    }
                }
            }
        }
        if(hitSphere){
            Vec normal = ptoHit - aux.getCenter();
            normal.getUnitVector();
            planeHit = Plane(ptoHit,normal,aux.getProps());
            planeHit.setKs(aux.getKs());
            planeHit.setKd(aux.getKd());
            planeHit.setAlpha(aux.getAlpha());
        }
        return hit;
    }

    RGB directLight(ReferenceSystem local, Plane p,Light l) {
        RGB color(1.0, 1.0, 1.0);
        Vec distance = l.getPosition() - local.getOrigin();
        Matrix localInv = local.getMatrix().inverse();
        Vec distanceLocal = localInv * distance;
        if(distanceLocal.getZ()>0) {
            Plane pAux;
            Sphere s;
            bool hit = false;
            Vec vp, point;
            Vec x = l.getPosition();
            for (int i = 0; i < numPlanos; ++i) {
                pAux = ps[i];
                if (pAux != p) {
                    if (p.intercepts(x, distance, point)) {
                        vp = point - x;
                        if (vp.modulus() < distance.modulus()) {
                            hit = true;
                        }
                    }
                }
            }
            if (!hit) {
                for (int i = 0; i < numSpheres; ++i) {
                    s = spheres[i];
                    if (s.intercepts(x, distance, point)) {
                        vp = point - x;
                        if (vp.modulus() < distance.modulus()) {
                            if(vp.modulus()>0.001){
                                hit = true;
                            }
                        }
                    }
                }
            }
            if (!hit) {
                color = color + (l.getPower() / pow(distance.modulus(), 2));
            } else {
                color = RGB(0.5, 0.5, 0.5);
            }
        }
        else{
            color = RGB(0.1,0.1,0.1);
        }
        return color;
    }

    // El centro de local es el punto de intersección
    float calculateDirectLight2(ReferenceSystem local){
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

    float randZeroToOne()
    {
        //double lower_bound = 0;
        //double upper_bound = 1;
        //std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
        //std::default_random_engine re;
        //return unif(re);
        //return rand() / (RAND_MAX + 1.);
        return r.giveNumber();
    }

    RGB getPixel(int i, int j){
        //cout<<x*this->y + y<<endl;
        return img[i*this->y + j];
    }

    void setPixel(int i, int j, RGB newPixel){
        img[i*this->y + j] = newPixel;
    }

    Vec u,l,f;
    Vec o;
    ReferenceSystem UCS;
    Plane ps[200];
    Sphere spheres[200];
    Light lights[10];
    RGB * img;
    int x,y;
    int numPlanos;
    int numSpheres;
    int numLights;
    RandomNumber r;
};

#endif //COMPUTER_GRAPHICS_RENDER_H
