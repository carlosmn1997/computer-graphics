//
// Created by Nicolas on 02/11/2018.
//

#ifndef COMPUTER_GRAPHICS_PLANE_H
#define COMPUTER_GRAPHICS_PLANE_H

#include "../Vec.h"
#include "../imaging/RGB.h"

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
        }
    }

    Plane() {}

    bool intercepts(Vec v){
        float i = v.getX()*normal.getX()+v.getY()*normal.getY()+v.getZ()*normal.getZ();
        return (i<0.001&&i>-0.001);
    }

    Vec intPoint(Vec v,Vec p){
        float a = normal.getX()*(origin.getX()-p.getX())+normal.getY()*(origin.getY()-p.getY());
        a += normal.getZ()*(origin.getZ()-p.getZ());
        float b = v.getX()*normal.getX()+v.getY()*normal.getY()+v.getZ()*normal.getZ();
        float t = a/b;
        Vec interception(p.getX()+t*v.getX(),p.getY()+t*v.getY(),p.getZ()+t*v.getZ(),1);
        return interception;
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
    Vec origin;
    Vec normal;
    RGB props;
};

#endif //COMPUTER_GRAPHICS_PLANE_H
