//
// Created by Carlos on 27/09/2018.
//

#ifndef COMPUTER_GRAPHICS_SPHERE_H
#define COMPUTER_GRAPHICS_SPHERE_H
#include "../Vec.h"
#include <cmath>
#include "../ReferenceSystem.h"
#include "../exception.h"
#include "../Vec.h"
#include "../ReferenceSystem.h"
#include "../imaging/RGB.h"

class Sphere
{
public:
    Sphere(){}

    Sphere(Vec center, Vec axis, Vec referenceCity){
        float radius = (center - referenceCity).modulus();
        // Check if  radius defined by the axis and by the distance between the center and
        //the reference city is the same (maximum error of 10−6)
        float difference = radius - axis.modulus()/2; // The radius
        if(abs(difference) > 0.000001){
            throw (Exception ("Radius not OK"));
        }
        this->center = center;
        this->axis = axis;
        this->referenceCity = referenceCity;

        // Now calculate the reference system of the own planet

        Vec k = axis;
        k.getUnitVector();
        Vec toRefCity = referenceCity - center;
        float cosBeta = (axis * toRefCity) / (axis.modulus() * toRefCity.modulus());
        float a1Scalar = toRefCity.modulus() * cosBeta;
        Vec a1 = a1Scalar * k;
        Vec a2 = toRefCity - a1;
        if(a2.modulus() == 0){
            std::cout<< "Reference city can't be in the poles";
            std::exit(1);
        }
        a2.getUnitVector();
        Vec i = a2;
        Vec j = Vec::crossProduct(i, k);
        this->r = ReferenceSystem(i, j, k, center);

        // this->r = ReferenceSystem(i, axis, k, center);

        // https://en.wikipedia.org/wiki/Vector_projection

    }

    const ReferenceSystem &getR() const {
        return r;
    }

    void setR(const ReferenceSystem &r) {
        Sphere::r = r;
    }

private:
    Vec center, axis, referenceCity;
    ReferenceSystem r;
    RGB props;
    RGB kd, ks, ksp, kr;
    float alpha;
public:

    const RGB &getKd() const {
        return kd;
    }

    void setKd(const RGB &kd) {
        Sphere::kd = kd;
    }

    const RGB &getKs() const {
        return ks;
    }

    void setKs(const RGB &ks) {
        Sphere::ks = ks;
    }

    const RGB &getKsp() const {
        return ksp;
    }

    void setKsp(const RGB &ksp) {
        Sphere::ksp = ksp;
    }

    const RGB &getKr() const {
        return kr;
    }

    void setKr(const RGB &kr) {
        Sphere::kr = kr;
    }

    float getAlpha() const {
        return alpha;
    }

    void setAlpha(float alpha) {
        Sphere::alpha = alpha;
    }

    const RGB &getProps() const {
        return props;
    }

    void setProps(const RGB &props) {
        Sphere::props = props;
    }

    const Vec &getCenter() const {
        return center;
    }

    void setCenter(const Vec &center) {
        Sphere::center = center;
    }

    const Vec &getAxis() const {
        return axis;
    }

    void setAxis(const Vec &axis) {
        Sphere::axis = axis;
    }

    const Vec &getReferenceCity() const {
        return referenceCity;
    }

    void setReferenceCity(const Vec &referenceCity) {
        Sphere::referenceCity = referenceCity;
    }

    float getRadio(){
        return axis.modulus()/2;
    }

    bool intercepts(Vec p, Vec v, Vec &point){
        float A,B,C;
        float vX,vY,vZ,pX,pY,pZ;
        float cX,cY,cZ;
        vX = v.getX();
        vY = v.getY();
        vZ = v.getZ();
        pX = p.getX();
        pY = p.getY();
        pZ = p.getZ();
        cX = center.getX();
        cY = center.getY();
        cZ = center.getZ();
        A = vX*vX+vY*vY+vZ*vZ; // A * t^2
        B = pX*vX - vX*cX + pY*vY - vY*cY + pZ*vZ - vZ*cZ; // B * t
        B = B*2;
        C = pX*pX - 2*pX*cX + cX*cX + pY*pY - 2*pY*cY + cY*cY + pZ*pZ - 2*pZ*cZ + cZ*cZ - getRadio()*getRadio(); // C * 1
        bool hit = true;
        if(A < 0.001 && A > -0.001){
            hit = false;
        }
        else{
            float root = B * B - 4 * A * C;
            if(root < -0.001){
                hit = false;
            }
            else{
                float t_pos = (-B + sqrt(root))/(2*A);
                float t_neg = (-B - sqrt(root))/(2*A);
                //cout << p.getType() << "-" << v.getType() << endl;
                Vec point_A,point_B;
                point_A.setX(p.getX()+t_pos*v.getX());
                point_A.setY(p.getY()+t_pos*v.getY());
                point_A.setZ(p.getZ()+t_pos*v.getZ());
                point_A.setType(1);
                point_B.setX(p.getX()+t_neg*v.getX());
                point_B.setY(p.getY()+t_neg*v.getY());
                point_B.setZ(p.getZ()+t_neg*v.getZ());
                point_B.setType(1);
                Vec dis_A = point_A-p;
                Vec dis_B = point_B-p;
                if(dis_A.modulus()<dis_B.modulus()){
                    point=point_A;
                }
                else{
                    point=point_B;
                }
            }
        }
        return hit;
    }

    bool contains( Vec p ){
        if(p.getType()!=1){
            std::cout<< "Expected point in sphere contains";
            std::exit(1);
        }
        Vec rad = p - center;
        float diff = rad.modulus() - getRadio();
        if(diff < 0.001 && diff > -0.001){
            return true;
        }
        else{
            return false;
        }
    }

};


#endif //COMPUTER_GRAPHICS_SPHERE_H
