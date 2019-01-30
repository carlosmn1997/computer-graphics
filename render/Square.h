//
// Created by Nicolas on 02/01/2019.
//

#ifndef COMPUTER_GRAPHICS_SQUARE_H
#define COMPUTER_GRAPHICS_SQUARE_H

#include "../Vec.h"
#include "../imaging/RGB.h"
#include "../ReferenceSystem.h"
#include "Plane.h"
#include "../imaging/Image.h"

class Square{

public:

    bool intercepts(Vec p, Vec v, Vec &point) {
        float b = v.getX() * normal.getX() + v.getY() * normal.getY() + v.getZ() * normal.getZ(); // denominador
        float a = normal.getX() * (origin.getX() - p.getX()) + normal.getY() * (origin.getY() - p.getY()); // numerador
        a += normal.getZ() * (origin.getZ() - p.getZ());
        if (b < 0.1 && b > -0.1) {
            return false;
        } else {
            float t = a / b;
            if (t <= 0) {
                return false;
            } else {
                point.setX(p.getX() + t * v.getX());
                point.setY(p.getY() + t * v.getY());
                point.setZ(p.getZ() + t * v.getZ());
                point.setType(1);
                Vec direction = point - origin;
                Vec directChanged = r.changeReferenceSystem(direction);
                if (directChanged.getX() < 0.00001 || directChanged.getY() < 0.00001) {
                    return false;
                } else if (directChanged.getX() > wide || directChanged.getY() > height ) {
                    return false;
                } else {
                    return true;
                }
            }
        }
    }

    Square() {}

    Square(const Vec &origin, const Vec &wide, const Vec &height,RGB props) : origin(origin) {
        Square::normal = Vec::crossProduct(height,wide);
        Square::normal.getUnitVector();
        Square::props = props;
        Vec i = wide;
        Vec j = height;
        Square::height = j.modulus();
        Square::wide = i.modulus();
        i.getUnitVector();
        j.getUnitVector();
        Square::r = ReferenceSystem(i,j,normal,origin);
        Square::p = Plane(origin,Square::normal,props);
        Square::p.setR(Square::r);
        Square::p.setAlt(Square::height);
        Square::p.setAnch(Square::wide);
    }

    Square(const Vec &origin, const Vec wide, const Vec height, const RGB &props, const RGB &kd, const RGB &ks,
            const RGB &ksp, const RGB &kr, float alpha)
                : origin(origin), props(props), kd(kd), ks(ks), ksp(ksp), kr(kr), alpha(alpha)
                {
                    Square::normal = Vec::crossProduct(height,wide);
                    Square::normal.getUnitVector();
                    Vec i = wide;
                    Vec j = height;
                    Square::height = i.modulus();
                    Square::wide = j.modulus();
                    i.getUnitVector();
                    j.getUnitVector();
                    Square::r = ReferenceSystem(i,j,normal,origin);
                    Square::p=Plane(origin,normal,props);
                    Square::p.setR(Square::r);
                    Square::p.setKd(kd);
                    Square::p.setKs(ks);
                    Square::p.setKsp(ksp);
                    Square::p.setKr(kr);
                    Square::p.setAlpha(alpha);
    }

    const Vec &getOrigin() const {
        return origin;
    }

    void setOrigin(const Vec &origin) {
        Square::origin = origin;
    }

    const RGB &getProps() const {
        return props;
    }

    void setProps(const RGB &props) {
        Square::props = props;
    }

    const RGB &getKd() const {
        return kd;
    }

    void setKd(const RGB &kd) {
        Square::kd = kd;
        p.setKd(kd);
    }

    const RGB &getKs() const {
        return ks;
    }

    void setKs(const RGB &ks) {
        Square::ks = ks;
        p.setKs(ks);
    }

    const RGB &getKsp() const {
        return ksp;
    }

    void setKsp(const RGB &ksp) {
        Square::ksp = ksp;
        p.setKsp(ksp);
    }

    const RGB &getKr() const {
        return kr;
    }

    void setKr(const RGB &kr) {
        Square::kr = kr;
        p.setKr(kr);
    }

    float getAlpha() const {
        return alpha;
    }

    void setAlpha(float alpha) {
        Square::alpha = alpha;
        p.setAlpha(alpha);
    }

    const Plane &getPlane(){
        return p;
    }

    bool isTextura(){
        return textura;
    }

    void setTextura(bool &b){
        Square::textura=b;
    }

    void addTextura(string filename){
        Square::p.addTextura(filename);
        Square::p.setTextura(true);
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
    Plane p;
    RGB kd, ks, ksp, kr;
    float alpha;
    float height, wide;
    bool textura;
    Image img;
    ReferenceSystem r;
};
#endif //COMPUTER_GRAPHICS_SQUARE_H
