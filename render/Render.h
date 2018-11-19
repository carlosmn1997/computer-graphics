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
        float uMod = u.modulus();
        float lMod = l.modulus();
        float fMod = f.modulus();
        for(int i=uMod;i>-uMod;i--){
            for(int j=-lMod;j<lMod;j++){
                Vec pixel(j+0.5,i-0.5,fMod,1);
                RGB x = pixelColor(pixel);
                img[72-i][j+128]= x;
            }
        }
    }

    void escribirImagen(string path){
        ofstream file;
        file.open(path);
        file << "P3" << endl;
        file << "#MAX=65535" << endl;
        file << "# mpi_atrium_3.ppm" << endl;
        file << "256 144" << endl;
        file << "10000" << endl;

        float coefficient = 65535/255;
        for (int i = 0; i < 144; i++){
            for (int j = 0; j < 256; j++){
                int R, G, B;
                R = max(img[i][j].getR() * coefficient,0);
                G = max(img[i][j].getB() * coefficient,0);
                B = max(img[i][j].getG() * coefficient,0);
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
        for(int i=0;i<numPlanos;++i){
            Plane p = ps[i];
            Vec point;
            if(p.intercepts(pixel,v,point)){
                hit=true;
                //cout<<"Intercepta  -->  " << i << endl;
                Vec vp = point - pixel;
                if(minMod==-1||minMod>vp.modulus()){
                    minMod=vp.modulus();
                    // vp es el rayo
                    // pixel es el punto de interseccion
                    color = renderEquation(pixel, vp, p);
                }
            }
        }
        for(int i=0;i<numSpheres;i++){
            Sphere s = spheres[i];
            Vec point;
            if(s.intercepts(pixel,v,point)){
                hit=true;
                cout<<"Intercepta esferita papa" <<endl;
                cout << point.getX() << "-" << point.getY() << "-" << point.getZ() << endl;
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
        // TODO Cambio de coordenadas
        // Sistema de coordenadas local respecto del punto x en el objeto o
        ReferenceSystem local = p.createReferenceSystemLocal(x);

        float directLight, incidenceAngle;
        directLight = calculateDirectLight(x);
        RGB BRDF = p.getProps();
        incidenceAngle = 1;
        return BRDF * directLight * incidenceAngle;

    }

    // El centro de local es el punto de intersección
    float calculateDirectLight(Vec x){
        //Vec x = local.changeReferenceSystem(local.getOrigin());
        float totalLight = 0;
        Vec light(1, 1, 1, 1);
        //Vec lightLocal = local.changeReferenceSystem(light);
        for (int i = 0; i < 1; i++){
            //TODO  Por cada geometría comprobar si intercepta o no, sino es sombra

            Vec rayo = light - x;
            // ¿Luz me viene de espaldas?
            //if (rayo.getZ()>=0) {
                // p / |c-x|^2
                totalLight += 1000000 / (pow((rayo).modulus(),2));
            //}
            //else{
          //      cout<<"kk"<<endl;
            //}
        }
        return totalLight;
    }

    Vec u,l,f;
    Vec o;
    Plane ps[200];
    Sphere spheres[200];
    float lights[10];
    RGB img[144][256];
    int numPlanos;
    int numSpheres;
    int numLigthts;
};

#endif //COMPUTER_GRAPHICS_RENDER_H
