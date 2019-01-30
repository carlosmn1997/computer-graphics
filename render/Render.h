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
#include "Square.h"


using namespace std;

class Render{

public:

    Render(const int x, const int y, const Vec &u, const Vec &l, const Vec &f, const Vec &o) : u(u), l(l), f(f), o(o) {
        this->numSpheres = 0;
        this->numPlanos = 0;
        this->numLights = 0;
        this->numSquares = 0;
        this->x=x;
        this->y=y;
        RGB negro(0,0,0);
        img = new RGB[x*y];
        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
               // this->setPixel(i,j,negro);
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

    void addSquare(Square s){
        this->squares[numSquares]=s;
        this->numSquares++;
    }

    void addLight(Light l){
        this->lights[numLights]=l;
        this->numLights++;
    }

    void trazar(){
        float uMod = u.modulus();
        float lMod = l.modulus();
        u.getUnitVector();
        l.getUnitVector();
        RandomNumber rn(0.001,0.019);
        Vec pixel;
        double restI,sumJ;
        int numPaths = 10; // NUMBER OF RAYS PER PIXEL
        for(double i=uMod;i>-uMod;i=i-0.02){
            for(double j=-lMod;j<lMod;j=j+0.02){
                RGB x(0,0,0);
                // cout << i << "->" << j << endl;
                for (int k = 0; k < numPaths; k++) {
                    int llevoX = (uMod-i)*50;
                    int llevoY = (lMod+j)*50;
                    if(llevoX == 701 && llevoY == 806)
                    {
                        cout << "x";
                    }
                    restI = rn.giveNumber();
                    sumJ = rn.giveNumber();
                    pixel = f + (i - restI) * u + (j + sumJ) * l;
                    pixel.setType(1);
                    RGB pixelAux = pixelColor(pixel);
                    if(isnan(pixelAux.getR())||isnan(pixelAux.getG())||isnan(pixelAux.getB())){
                        cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
                    }
                    x = x + pixelAux;//pixelColor(pixel);
                }
                x = x / numPaths;
                this->setPixel((uMod-i)*50,(lMod+j)*50,x);
                if((uMod - i) * 50 > 192) {
                    //cout << "Escribo i=" << (uMod - i) * 50 << " j=" << (lMod + j) * 50 << endl;
                }
            }
            cout << "Escribo i=" << (uMod-i)*50 << " de " << (uMod) * 100 <<endl;
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
        file << "# salida.ppm" << endl;
        file << "1280 720" << endl;
        file << "10000000" << endl;

        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
                int R, G, B;
                if(i==73&&j==54){
                    cout<<"PASA"<<endl;
                }
                RGB aux = this->getPixel(i,j);
                R = max(aux.getR(),0);
                G = max(aux.getG(),0);
                B = max(aux.getB(),0);
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
        image.gammaCurve(2.5);
        //image.clamping();
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
        Square sq;
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
        for(int i=0;i<numSquares;++i){
            sq = squares[i];
            if(sq.intercepts(pixel,v,point)){
                hit=true;
                //cout<<"Intercepta  -->  " << i << endl;
                vp = point - pixel;
                distance = vp.modulus();
                if(minMod==-1||minMod>distance){
                    minMod=vp.modulus();
                    planeHit = sq.getPlane();
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
            if(s.intercepts(pixel,v,point,false)){
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
            planeHit.setKsp(sphereHit.getKsp());
            planeHit.setKr(sphereHit.getKr());
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
        if(p.isTextura()){
            color = p.getPixelFromImg(x);
        }
        int iteraciones=0;
        while (!absorcion && interseccion && !emitter && !p.isTextura()){
            iteraciones++;
            // Sistema de coordenadas local respecto del punto x en el objeto o
            ReferenceSystem r = p.getR();
            Vec iref = r.getI();
            Vec jref = r.getJ();
            Vec kref = r.getK();
            if(isnan(iref.getX())||isnan(iref.getY())||isnan(iref.getZ())){
                   cout << "I" << iref.getX() << iref.getY() << iref.getZ() << " ITERACION " << iteraciones << endl;
            }
            if(isnan(jref.getX())||isnan(jref.getY())||isnan(jref.getZ())){
                cout << "J" << jref.getX() << jref.getY() << jref.getZ() << " ITERACION " << iteraciones << endl;
            }
            if(isnan(kref.getX())||isnan(kref.getY())||isnan(kref.getZ())){
                cout << "Z" << kref.getX() << kref.getY() << kref.getZ() << " ITERACION " << iteraciones << endl;
            }
            local = p.createReferenceSystemLocal(x);
            iref=local.getI();
            jref=local.getJ();
            kref=local.getK();
            if(isnan(iref.getX())||isnan(iref.getY())||isnan(iref.getZ())){
                cout << "I" << iref.getX() << iref.getY() << iref.getZ() << " ITERACION " << iteraciones << endl;
            }
            if(isnan(jref.getX())||isnan(jref.getY())||isnan(jref.getZ())){
                cout << "J" << jref.getX() << jref.getY() << jref.getZ() << " ITERACION " << iteraciones << endl;
            }
            if(isnan(kref.getX())||isnan(kref.getY())||isnan(kref.getZ())){
                cout << "Z" << kref.getX() << kref.getY() << kref.getZ() << " ITERACION " << iteraciones << endl;
            }
            referenceSystem = local.getMatrix().inverse();
            x = referenceSystem*x;
            wo.getUnitVector();

            if(p.isEmitter()){
                color = color + acumulado * p.getProps();
                emitter = true;
            }

            // Next event estimation
            for(int i=0;i<numLights;++i){
                wiDirecta = lights[i].getPosition()-local.getOrigin();
                // Calcular el reflejado
                wiDirecta.getUnitVector();
                wiDirecta = wiDirecta * -1; // Hay que darle la vuelta
                Vec reflected = wiDirecta - 2 * local.getK() *  (local.getK() * wiDirecta);
                // Hacer phong con el reflejado
                RGB phong = phongBRDF(p.getKd(),p.getKs(),p.getAlpha(),wo, reflected);
                if(isnan(phong.getR())||isnan(phong.getG())||isnan(phong.getB())){
                    cout<<"FALLA PHONG"<<endl;
                }
                //RGB phong = p.getKd();
                RGB directLightVal = directLight(local, p,lights[i]);
                if(isnan(directLightVal.getR())||isnan(directLightVal.getG())||isnan(directLightVal.getB())){
                    cout<<"FALLA DIRECT LIGHT"<<endl;
                }
                // Aqui hay que poner la propiedad geometrica ya que no estamos muestreando
                color = color + acumulado * phong * directLightVal * abs(local.getK()*wiDirecta);
                if(isnan(phong.getR())||isnan(phong.getG())||isnan(phong.getB())){
                    cout<<"FALLA LA PROP GEOM"<<endl;
                }
                //emitter = true;
            }

            // TODO sacar los valores, si es un emisor se divide para 0 pero da igual porque es absorcion
            RGB kdAux = p.getKd();
            RGB ksAux = p.getKs();
            RGB kspAux = p.getKsp();
            RGB krAux = p.getKr();

            // TODO normalizar entre 0 y 0.9
            normalizeRR(kdAux, ksAux, kspAux, krAux);
            if(isnan(kdAux.getR())||isnan(kdAux.getG())||isnan(kdAux.getB())){
                cout<<"FALLA NORM"<<endl;
            }
            if(isnan(ksAux.getR())||isnan(ksAux.getG())||isnan(ksAux.getB())){
                cout<<"FALLA NORM"<<endl;
            }
            if(isnan(kspAux.getR())||isnan(kspAux.getG())||isnan(kspAux.getB())){
                cout<<"FALLA NORM"<<endl;
            }
            if(isnan(krAux.getR())||isnan(krAux.getG())||isnan(krAux.getB())){
                cout<<"FALLA NORM"<<endl;
            }
            kd = kdAux.getMax();
            ks = ksAux.getMax();
            ksp = kspAux.getMax();
            kr = krAux.getMax();

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
                if(isnan(wi.getX())||isnan(wi.getY())||isnan(wi.getZ())){
                    cout<<"FALLA RANDOM"<<endl;
                    cout<<randPoint.getX()<<randPoint.getY()<<randPoint.getZ()<<endl;
                    cout<<wi.getX()<<wi.getY()<<wi.getZ()<<endl;
                }
                wi.getUnitVector();

                if(isnan(wi.getX())||isnan(wi.getY())||isnan(wi.getZ())){
                    cout<<"FALLA UNITARIO"<<endl;
                }

                // To global coordinates
                // TODO no estoy seguro de wo

                Vec wiAntiguo=wi;
                wi = local.getMatrix()*wi;
                x = local.getMatrix()*x;

                if(isnan(wi.getX())||isnan(wi.getY())||isnan(wi.getZ())){
                    cout<<"FALLA CAMBIO"<<endl;
                    cout<<wiAntiguo.getX()<<","<<wiAntiguo.getY()<<","<<wiAntiguo.getZ()<<endl;
                }

                // PHONG BIEN
                // Reflejado del rayo  saliente
                Vec reflected = wi - 2 * local.getK() *  (local.getK() * wi);

                if(isnan(reflected.getX())||isnan(reflected.getY())||isnan(reflected.getZ())){
                    cout<<"FALLA REFLECTED"<<endl;
                }

                // Luz directa
                //color = color + (p.getKd() / M_PI)*directLight(local, p);
                // TODO phong
                // TODO acumular angulo de incidencia
                acumulado = acumulado * M_PI * phongBRDF(p.getKd(),p.getKs(),p.getAlpha(),wo, reflected);
                if(isnan(acumulado.getR())||isnan(acumulado.getG())||isnan(acumulado.getB())){
                    //cout<<"FALLA ANG INC"<<endl;
                    //cout << p.getAlpha() << "---" << p.getKd().getR() << "-" << p.getKd().getG() << "-" <<p.getKd().getB();
                }
                //acumulado = acumulado * phongBRDF(p.getKd(),p.getKs(),p.getAlpha(),wo, wi) / (2 * M_PI); // Se divide para la pdf
                // TODO dividir para el angulo de incidencia con la probabilidad esa
                acumulado = acumulado / (kd + ks); // TODO seguro que esto es asi?
                if(isnan(acumulado.getR())||isnan(acumulado.getG())||isnan(acumulado.getB())){
                    //cout<<"FALLA ANG INC con prob"<<endl;
                }

                //wo = Vec(1, -1, -1, DIRECTION);
                xViejo = x;
                interseccion = nearestIntersection(wi, x, p, x, p, local,false);

                wo = x - xViejo;
            }
                // Perfect specular
            else if (kd+ks < rr && rr < ksp + kd + ks){
                x = local.getMatrix()*x;
                Vec n = local.getK();//referenceSystem*n;
                wi = wo - 2*n*(wo*n);// rayo saliente desde donde miro
                wi.getUnitVector();
                acumulado = acumulado * (specularReflectionBRDF(p.getKsp(), n, wi) * abs(n*wi) / ksp);
                if(isnan(acumulado.getR())||isnan(acumulado.getG())||isnan(acumulado.getB())){
                    //cout<<"FALLA ESPECULAR"<<endl;
                }
                interseccion = nearestIntersection(wi, x, p, x, p, local,false);
                wo = wi;
            }
            else if(kd+ks+ksp < rr && rr < kr + kd + ks + ksp){
                if(refraction(p, wo, wi)) {
                    x = local.getMatrix()*x;
                    p.setNormal(p.getNormal() * -1);
                    local.setK(local.getK() * -1);
                    nearestIntersection(wi, x, p, x, p, local,true);
                    wo = wi;
                    if(refraction(p, wo, wi)){
                        acumulado = acumulado * glassRefractionBTDF(p.getKr(),local.getK(),wi);
                        if(isnan(acumulado.getR())||isnan(acumulado.getG())||isnan(acumulado.getB())){
                            //cout<<"FALLA REFRACT 1"<<endl;
                        }
                        interseccion = nearestIntersection(wi, x, p, x, p, local,false);
                    }
                    else{
                        acumulado = acumulado * specularReflectionBRDF(p.getKsp(), local.getK(), wi);
                        if(isnan(acumulado.getR())||isnan(acumulado.getG())||isnan(acumulado.getB())){
                            //cout<<"FALLA REFRACT 2"<<endl;
                        }
                        interseccion = nearestIntersection(wi, x, p, x, p, local,false);
                    }
                }
                else{
                    acumulado = acumulado * specularReflectionBRDF(p.getKsp(), local.getK(), wi);
                    if(isnan(acumulado.getR())||isnan(acumulado.getG())||isnan(acumulado.getB())){
                        //cout<<"FALLA ESTO RARO"<<endl;
                    }
                    interseccion = nearestIntersection(wi, x, p, x, p, local,false);
                }
                wo = wi;
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
        if(isnan(part1.getR())||isnan(part1.getG())||isnan(part1.getB())){
            //cout<<"FALLA PHONG"<<endl;
            //cout<< wo.getX() << "-" << wo.getY() << "-" << wo.getZ() << endl;
            //cout<< wi.getX() << "-" << wi.getY() << "-" << wi.getZ() << endl;
        }
        return part1;
    }

    RGB specularReflectionBRDF(RGB ksp, Vec n, Vec wi){
        //float aux2 = abs(wi*n);
        //float aux3 = wi*n;
        //float aux = (M_PI*abs(wi*n));
        RGB reflection = ksp * 1 / (M_PI*abs(wi*n));
        return reflection;
    }

    RGB glassRefractionBTDF(RGB kr, Vec n, Vec wi){
        RGB reflection = kr * 1 / (M_PI*abs(wi*n));
        return reflection;
    }

public:
    bool refraction(Plane p, Vec wo, Vec& wi){
        float coeff = 1/1.6; //refraction coefficient between air and cristal
        float cosWo = p.getNormal() * wo;
        float sqr = 1 - coeff * coeff * ( 1 - cosWo * cosWo);
        if(cosWo<0){ // Ray going into the ball
            cosWo = -cosWo;
        }
        else{ // Ray going outside the ball
            p.setNormal((p.getNormal()*-1));
            coeff = 1.5;
        }
        if(sqr>=0) {
            wi = coeff * wo + (coeff * cosWo - sqrtf(sqr)) * p.getNormal();
            return true;
        }
        else{
            return false;
        }
    }
private:
    // v -> rayo
    // x -> origen del rayo
    bool nearestIntersection(Vec v, Vec x, Plane myPlane, Vec& ptoHit, Plane& planeHit, ReferenceSystem r,bool refraction){
        float minMod=-1;
        RGB color(0,0,0);
        bool hit=false;
        Vec point;
        Vec vp;
        Plane p;
        Square sq;
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
        for(int i=0;i<numSquares;++i){
            sq = squares[i];
            if (sq.getPlane() != myPlane){
                if(sq.intercepts(x,v,point)){
                    hit=true;
                    vp = point - x;
                    if(minMod==-1||minMod>vp.modulus()){
                        minMod=vp.modulus();
                        ptoHit = point;
                        planeHit = sq.getPlane();
                    }
                }
            }
        }
        for(int i=0;i<numSpheres;++i){
            s = spheres[i];
            if (!s.contains(myPlane.getOrigin())||refraction){
                if(s.intercepts(x,v,point,refraction)){
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
            planeHit.setKsp(aux.getKsp());
            planeHit.setKr(aux.getKr());
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
            Square sq;
            bool hit = false;
            Vec vp, point;
            Vec x = local.getOrigin();
            for (int i = 0; i < numPlanos; ++i) {
                pAux = ps[i];
                if (pAux != p) {
                    if (pAux.intercepts(x, distance, point)) {
                        vp = point - x;
                        if (vp.modulus() < distance.modulus()) {
                            hit = true;
                        }
                    }
                }
            }
            if(!hit){
                for (int i = 0; i < numSquares; ++i) {
                    sq = squares[i];
                    if (sq.getPlane() != p) {
                        if (sq.intercepts(x, distance, point)) {
                            vp = point - x;
                            if (vp.modulus() < distance.modulus()) {
                                hit = true;
                            }
                        }
                    }
                }
            }
            if (!hit) {
                for (int i = 0; i < numSpheres; ++i) {
                    s = spheres[i];
                    if (s.intercepts(x, distance, point,false)) {
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
                //color = color + (l.getPower() / pow(distance.modulus(), 2));
                color = (l.getPower() / pow(distance.modulus(), 2));
            } else {
                color = RGB(0.5, 0.5, 0.5);
            }
        }
        else{
            color = RGB(0.1,0.1,0.1);
        }
        return color;
    }


    // Normalizar los valores de la ruleta rusa para asegurar absorción
    void normalizeRR(RGB& kd, RGB& ks, RGB& ksp, RGB& kr){
        float maxKd = kd.getMax();
        float maxKs = ks.getMax();
        float phong = maxKs + maxKd;
        float maxKsp = ksp.getMax();
        float maxKr = kr.getMax();

        float denominador = (phong + maxKsp + maxKr) * 1.1; // Para asegurarnos un 10% de absorción
        if(denominador!=0) {
            kd = kd / denominador;
            ks = ks / denominador;
            ksp = ksp / denominador;
            kr = kr / denominador;
        }
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
        if(i>100&&i<102) {
            //cout << i << "-" << j << endl;
        }
        if(i==101&&j==806){
            cout<<"BUENO->"<<endl;
            cout<<newPixel.getR()<<"-"<<newPixel.getB()<<"-"<<newPixel.getG()<<endl;
        }
        else if((i==100&&j==806)||i==101&&j==807){
            cout<<newPixel.getR()<<"-"<<newPixel.getB()<<"-"<<newPixel.getG()<<endl;
        }
        img[i*this->y + j] = newPixel;
    }

    Vec u,l,f;
    Vec o;
    ReferenceSystem UCS;
    Plane ps[30];
    Sphere spheres[30];
    Square squares[30];
    Light lights[10];
    RGB * img;
    int x,y;
    int numPlanos;
    int numSpheres;
    int numSquares;
    int numLights;
    RandomNumber r;
};

#endif //COMPUTER_GRAPHICS_RENDER_H
