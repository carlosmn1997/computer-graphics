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

private:
    float A,B,C;
public:

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

    bool intercepts(Vec p, Vec v, Vec &z){
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
        B = pX*vX + vX*cX + pY*vY + vY*cY + pZ*vZ + vZ*cZ; // B * t
        B = B*2;
        C = pX*pX - 2*pX*cX + cX*cX + pY*pY - 2*pY*cY + cY*cY + pZ*pZ - 2*pZ*cZ + cZ*cZ - getRadio(); // C * 1
        bool hit = true;
        if(A < 0.001 || A > -0.001){
            hit = false;
        }
        else{
            float root = B * B - 4 * A * C;
            if(root < -0.001){
                hit = false;
            }
            else{
                float t_pos = (-B + sqrt(B*B-4*A*C))/2*A;
                float t_neg = (-B - sqrt(B*B-4*A*C))/2*A;
                Vec point_A(p+t_pos*v);
                Vec point_B(p+t_neg*v);
                Vec dis_A = point_A-p;
                Vec dis_B = point_B-p;
                if(dis_A.modulus()<dis_B.modulus()){
                    z=point_A;
                }
                else{
                    z=point_B;
                }
            }
        }
        return hit;
    }

};


#endif //COMPUTER_GRAPHICS_SPHERE_H
