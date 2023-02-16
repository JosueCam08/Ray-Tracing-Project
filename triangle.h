#ifndef TRIANGLE.H
#define TRIANGLE.H

#include "hittable.h"
#include "vec3.h"

// Clase del triangulo en el plano para la creacion de imagenes primitivas
class triangle : public hittable {
    public:
        triangle() {}
        // Puntos del triangulo - Material del triangulo
        triangle(point3 p1, point3 p2, point3 p3, shared_ptr<material> m)
            : v1(p1), v2(p2), v3(p3), mat_ptr(m) {
                vec3 direction = cross( (p2 - p1), (p3 - p1));
                normal = unit_vector(direction);
            };

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 v1, v2, v3;
        vec3 normal;
        shared_ptr<material> mat_ptr;

};

// Funcion que identifica si un rayo intersecta el triangulo
bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    
    double denominator = dot(normal, r.dir);

    if (abs(denominator) > 0.0001f){
        // Obtenemos el valor 
        float intersection_t = dot((v1 - r.orig), normal) / denominator;

        if(t_min <= intersection_t && t_max >= intersection_t && intersection_t){
            
            // Punto de interseccion
            point3 p = r.at(intersection_t);

            point3 a = v1 - p;
            point3 b = v2 - p;
            point3 c = v3 - p;

            vec3 u = unit_vector(cross(b, c));
            vec3 v = unit_vector(cross(c, a));
            vec3 w = unit_vector(cross(a, b));

            // Comprobamos si el valor de t intersecta el triangulo
            if( (u-v).length_squared() > 0.0001)
                return false;

            if((u-w).length_squared() > 0.0001 )
                return false;

            rec.t = intersection_t;
            rec.p = r.at(rec.t);
            rec.set_face_normal(r, normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}

#endif