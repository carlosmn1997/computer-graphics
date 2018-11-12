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

    // p -> centro pixel
    // v -> vector que pasa por el centro del pixel
    // point -> punto de intersección
    bool intercepts(Vec p, Vec v, Vec &point){
        float b = v.getX()*normal.getX()+v.getY()*normal.getY()+v.getZ()*normal.getZ(); // denominador
        float a = normal.getX()*(origin.getX()-p.getX())+normal.getY()*(origin.getY()-p.getY()); // numerador
        a += normal.getZ()*(origin.getZ()-p.getZ());
        if(b<0.1&&b>-0.1){
            return false;
        }
        else{
            float t = a/b;
            if(t < -0.001){
                return false;
            }
            else{
                point.setX(p.getX()+t*v.getX());
                point.setY(p.getY()+t*v.getY());
                point.setZ(p.getZ()+t*v.getZ());
                point.setType(1);
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

private:
    void createRefSystem(){
        d = -origin.getX()*normal.getX() -origin.getY()*normal.getY() - origin.getZ()*normal.getZ();
        float z=(-d -normal.getX()-normal.getY())/normal.getZ();
        z -= normal.getZ();
        Vec p(origin.getX()+1,origin.getY()+1,z,1);
        Vec i = p-origin;
        Vec k = Vec::crossProduct(i,normal);
        r.setI(i);
        r.setJ(normal);
        r.setK(k);
        r.setOrigin(origin);
    }

    Vec origin;
    Vec normal;
    RGB props;
    ReferenceSystem r;
    float d;
};

#endif //COMPUTER_GRAPHICS_PLANE_H
