//
// Created by Nicolas on 02/11/2018.
//

#ifndef COMPUTER_GRAPHICS_PLANE_H
#define COMPUTER_GRAPHICS_PLANE_H

#include "../Vec.h"
#include "../imaging/RGB.h"
#include "../ReferenceSystem.h"

class Plane{
public:
    Plane(Vec origin,Vec normal,RGB props){
        if (origin.getType()==0){
            cout << "NO SE PUEDE ORIGEN PLANO"<<endl;
        }
        else if(normal.getType()==1){
            cout << "NO SE PUEDE NORMAL PLANO"<<endl;
        }
        else{
            this->origin=origin;
            this->normal=normal;
            this->props=props;
            createRefSystem();
        }
    }

    Plane() {}

    // p -> centro pixel en globales
    // v -> vector que pasa por el centro del pixel en globales
    // point -> punto de intersección
    // r -> respecto de qué sistema nos estan mirando
    bool intercepts(Vec p, Vec v, Vec &point, ReferenceSystem r) {
        // Cambiando el sistema de referencia
        Matrix m = r.getMatrix().inverse();
        //Vec origin = m * this->origin;
        //Vec normal = m * this->normal;
        float b = v.getX() * normal.getX() + v.getY() * normal.getY() + v.getZ() * normal.getZ(); // denominador
        float a = normal.getX() * (origin.getX() - p.getX()) + normal.getY() * (origin.getY() - p.getY()); // numerador
        a += normal.getZ() * (origin.getZ() - p.getZ());
        if (b < 0.1 && b > -0.1) {
            return false;
        } else {
            float t = a / b;
            point.setX(p.getX() + t * v.getX());
            point.setY(p.getY() + t * v.getY());
            point.setZ(p.getZ() + t * v.getZ());
            point.setType(1);
            if (t < -0.001) {
                return false;
            } else {
                return true;
            }
        }
    }

    const Vec &getOrigin() const {
        return origin;
    }

    void setOrigin(const Vec &origin) {
        Plane::origin = origin;
    }

    const Vec &getNormal() const {
        return normal;
    }

    void setNormal(const Vec &normal) {
        Plane::normal = normal;
    }

    const RGB &getProps() const {
        return props;
    }

    void setProps(const RGB &props) {
        Plane::props = props;
    }

    ReferenceSystem getR(){
        return r;
    }

    ReferenceSystem createReferenceSystemLocal(Vec x){
        ReferenceSystem local;
        local.setOrigin(x);
        local.setI(r.getI());
        local.setJ(r.getJ());
        local.setK(r.getK());
        return local;
    }

private:
    void createRefSystem(){
        float x,y,z;
        bool xDone = false;
        bool yDone=false;
        bool zDone=false;
        int numberDone=0;
        if(normal.getX()==0){
            xDone = true;
            x = 1;
            numberDone++;
        }

        if(normal.getY()==0){
            yDone = true;
            y = 1;
            numberDone++;
        }

        if(normal.getZ()==0){
            zDone = true;
            z = 1;
            numberDone++;
        }

        if(numberDone==2){
            if(!xDone){
                x = 0;
            }
            else if(!yDone){
                y = 0;
            }
            else{
                z = 0;
            }
        }
        else if(numberDone==1){
            if(xDone){
                y = 1;
                z = -normal.getY()/normal.getZ();
            }
            else if(!yDone){
                x = 1;
                z = -normal.getX()/normal.getZ();
            }
            else{
                x = 1;
                y = -normal.getX()/normal.getY();
            }
        }
        else{
            x = 1;
            y = 1;
            z = (-normal.getY()-normal.getX())/normal.getZ();
        }

        Vec i(x,y,z,0);
        i.getUnitVector();

        Vec k = Vec::crossProduct(i,normal);
        k.getUnitVector();

        r.setI(i);
        r.setJ(k);
        r.setK(normal);
        r.setOrigin(origin);
    }

public:
    bool operator==(const Plane &rhs) const {
        return origin == rhs.origin &&
               normal == rhs.normal &&
               props == rhs.props &&
               kd == rhs.kd &&
               ks == rhs.ks &&
               alpha == rhs.alpha &&
               ksp == rhs.ksp &&
               kr == rhs.kr &&
               r == rhs.r &&
               d == rhs.d;
    }

    bool operator!=(const Plane &rhs) const {
        return !(rhs == *this);
    }

private:

    Vec origin;
    Vec normal;
    RGB props;
    // kd -> diffuse coefficient
    // ks -> specular coefficient
    // alpha -> shininess
    // ksp -> perfect specular reflection
    // kr -> perfect specular refraction
    RGB kd, ks, alpha, ksp, kr;
public:
    const RGB &getKd() const {
        return kd;
    }

    void setKd(const RGB &kd) {
        Plane::kd = kd;
    }

    const RGB &getKs() const {
        return ks;
    }

    void setKs(const RGB &ks) {
        Plane::ks = ks;
    }

    const RGB &getAlpha() const {
        return alpha;
    }

    void setAlpha(const RGB &alpha) {
        Plane::alpha = alpha;
    }

    const RGB &getKsp() const {
        return ksp;
    }

    void setKsp(const RGB &ksp) {
        Plane::ksp = ksp;
    }

    const RGB &getKr() const {
        return kr;
    }

    void setKr(const RGB &kr) {
        Plane::kr = kr;
    }

    void setR(const ReferenceSystem &r) {
        Plane::r = r;
    }

    float getD() const {
        return d;
    }

    void setD(float d) {
        Plane::d = d;
    }

    bool isEmitter(){
        return props.getR() > 0 || props.getG() > 0 || props.getB() > 0;
    }

private:
    ReferenceSystem r;
    float d;
};

#endif //COMPUTER_GRAPHICS_PLANE_H
