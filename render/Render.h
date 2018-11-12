//
// Created by Nicolas on 02/11/2018.
//

#ifndef COMPUTER_GRAPHICS_RENDER_H
#define COMPUTER_GRAPHICS_RENDER_H

#include <fstream>
#include "../imaging/RGB.h"
#include "Plane.h"
#include "Sphere.h"

class Render{

public:

    Render(const Vec &u, const Vec &l, const Vec &f, const Vec &o) : u(u), l(l), f(f), o(o) {
        this->numSpheres = 0;
        this->numPlanos = 0;
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
        for(int i=0;i<l.modulus();i++){
            for(int j=0;j<u.modulus();j++){
                Vec pixel(i+0.5,j+0.5,f.modulus(),1);
                //cout<<"nuevo pixel"<<endl;
                RGB x = pixelColor(pixel);
                if(x.getR()<254.90){
                  //  cout<<"CCACAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa" <<endl;
                }
                img[i][j]= x;
            }
            cout<<"Voy por: "<<i<<endl;
        }
    }

    void escribirImagen(string path){
        ofstream file;
        file.open(path);
        file << "P3" << endl;
        file << "256 144" << endl;
        file << "65535" << endl;

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
        Vec v = pixel-o;
        float minMod=-1;
        RGB color(0,0,0);
        Vec ptoHit;
        Plane planeHit;
        bool hit=false;
        for(int i=0;i<numPlanos;++i){
            if(i == 1){
                i = 1;
            }
            Plane p = ps[i];
            Vec point;
            if(p.intercepts(pixel,v,point)){
                hit=true;
                //cout<<"Intercepta"<<endl;
                Vec vp = point - pixel;
                if(minMod==-1||minMod>vp.modulus()){
                    minMod=vp.modulus();
                    ptoHit = point;
                    color = p.getProps();
                }
            }
        }
        for(int i=0;i<numSpheres;i++){
            //cout<<"No entra"<<endl;
            Sphere s = spheres[i];
            Vec point;
            if(s.intercepts(pixel,v,point)){
                hit=true;
                Vec vp = point - pixel;
                if(minMod==-1||minMod>vp.modulus()){
                    minMod=vp.modulus();
                    ptoHit = point;
                    color = s.getProps();
                    if (color.getR() <= 0){
                        //cout<<"kkkkk"<<endl;
                    }
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

    Vec u,l,f;
    Vec o;
    Plane ps[200];
    Sphere spheres[200];
    RGB img[144][256];
    int numPlanos;
    int numSpheres;
};

#endif //COMPUTER_GRAPHICS_RENDER_H
