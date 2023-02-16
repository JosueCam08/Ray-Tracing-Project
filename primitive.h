#ifndef PRIMITIVE.H
#define PRIMITIVE.H

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "triangle.h"

#include <iostream>

// Clase primitivas la cual genera la figura con base a triangulos en el plano
class primitive{
    private:
        std::vector<point3> *points;
        std::vector< std::vector<int> > *vertex;
        int material;
        hittable_list *world;


    public:
        primitive() {}

        // Inicializa los valores del constructor
        primitive(std::vector<point3> *c_points, std::vector< std::vector<int> > *c_vertex, int c_option, hittable_list *c_world) {
            points = c_points;
            vertex = c_vertex;
            material = c_option;
            world = c_world;
        }

        // Dibuja el triangulo con la informacion dada
        void draw(){
            // Elije el tipo de material
            if(material == 1){
                auto material1 = make_shared<dielectric>(1.5);
                for(auto v : (*vertex))
                    world->add(make_shared<triangle>((*points)[v[0]], (*points)[v[1]], (*points)[v[2]], material1));
            }else if(material == 2){
                auto material2 = make_shared<lambertian>(color(0.1, 0.2, 0.5));
                for(auto v : (*vertex))
                    world->add(make_shared<triangle>((*points)[v[0]], (*points)[v[1]], (*points)[v[2]], material2));
            }else{
                auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
                for(auto v : (*vertex))
                    world->add(make_shared<triangle>((*points)[v[0]], (*points)[v[1]], (*points)[v[2]], material3));
            }
        }
};
#endif