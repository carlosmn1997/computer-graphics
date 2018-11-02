//
// Created by Nicolas on 02/11/2018.
//

#ifndef COMPUTER_GRAPHICS_RENDER_H
#define COMPUTER_GRAPHICS_RENDER_H

#include "../Vec.h"
#include "../imaging/RGB.h"
#include "Plane.h"

class Render{

public:

    Render(const Vec &u, const Vec &l, const Vec &f, const Vec &o) : u(u), l(l), f(f), o(o) {}

    Render() {}

    void addPlane(Plane p){
        this->ps[numPlanos]=p;
        this->numPlanos++;
    }

    void trazar(){
        for(int i=0;i<144;i++){
            for(int j=0;j<256;j++){
                Vec pixel(l.modulus()-0.5*i,u.modulus()-0.5*j,f.modulus(),1);
                img[i][j]=pixelColor(pixel);
            }
        }
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
        RGB color(255,255,255);
        for(int i=0;i<numPlanos;++i){
            Plane p = ps[i];
            if(p.intercepts(v)){
                Vec point = p.intPoint(v,pixel);
                Vec vp = point - pixel;
                if(minMod==-1||minMod>vp.modulus()){
                    minMod=vp.modulus();
                    color=p.getProps();
                }
            }
        }
        return color;
    }

    Vec u,l,f;
    Vec o;
    Plane ps[200];
    RGB img[144][256];
    int numPlanos;
};

#endif //COMPUTER_GRAPHICS_RENDER_H
