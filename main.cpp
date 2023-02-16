#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "triangle.h"
#include "primitive.h"

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

point3 getPoint(std::string str){
    std::stringstream strInput;
    strInput << str;
    
    double d1, d2, d3;
    std::string value = "";
        
    for(int i = 0; i < 3; i++){
        strInput >> value;
        if(i == 0)
            std::stringstream(value) >> d1;
        if(i == 1)
            std::stringstream(value) >> d2;
        if(i == 2)
            std::stringstream(value) >> d3;
        value = "";
    }

    return point3(d1, d2, d3);
}

std::vector<int> getVertex(std::string str){
    std::stringstream strInput;
    strInput << str;
    
    std::vector<int> v;
    std::string value = "";
    int aux;
        
    for(int i = 0; i < 3; i++){
        strInput >> value;
        if(std::stringstream(value) >> aux)
            v.push_back(aux);
        value = "";
    }

    return v;
}

// Presenta las figuras en el world
hittable_list scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    // ifstream para la lectura del archivo
    std::ifstream fin ("info.txt");

    // Numero de figuras primitivas
    std::string str;
    getline(fin, str);
    int n = stoi(str);

    // Procesamiento de cada figura
    for(int j= 0; j < n; j++){
        std::stringstream strInput;
        str = "";
        getline(fin, str);
        strInput << str;

        // Numero de puntos, vertices y tipo de material
        int P, V, M, aux;
        std::string value = "";
        for(int i = 0; i < 3; i++){
            strInput >> value;
            if(i == 0)
                std::stringstream(value) >> P;
            if(i == 1)
                std::stringstream(value) >> V;
            if(i == 2)
                std::stringstream(value) >> M;
            value = "";
        }

        // Procesamiento de puntos
        std::vector<point3> vPoints;
        for(int i = 0; i < P; i++){
            getline(fin, str);
            vPoints.push_back(getPoint(str));
        }
        
        // Procesamiento de vertices
        std::vector< std::vector<int> > vVertex;
        for(int i = 0; i < V; i++){
            getline(fin, str);
            vVertex.push_back(getVertex(str));
        }

        // Procesamiento de la figura primitiva y adicion a world
        primitive c_primitive(&vPoints, &vVertex, M, &world);
        c_primitive.draw();
    }

    // Numero de esferas
    getline(fin, str);
    int m = stoi(str);

    // Procesamiento de cada esfera
    for(int j = 0; j < m; j++){
        std::vector<double> spheresInfo;

        getline(fin, str);
        std::stringstream newstrInput;
        newstrInput << str;

        // Procesamiento de la coordenada centro, radio y tipo de material
        std::string value = "";
        double vSphere;
        for(int i = 0; i < 5; i++){
            newstrInput >> value;
            if(std::stringstream(value) >> vSphere)
                spheresInfo.push_back(vSphere);
            value = "";
        }

        if((int)spheresInfo[4] == 1){
            auto material1 = make_shared<dielectric>(1.5);
            world.add(make_shared<sphere>(point3(spheresInfo[0], spheresInfo[1], spheresInfo[2]), spheresInfo[3], material1));
        }else if((int)spheresInfo[4] == 2){
            auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
            world.add(make_shared<sphere>(point3(spheresInfo[0], spheresInfo[1], spheresInfo[2]), spheresInfo[3], material2));
        }else{
            auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
            world.add(make_shared<sphere>(point3(spheresInfo[0], spheresInfo[1], spheresInfo[2]), spheresInfo[3], material3));
        }


    }

    return world;
}

int main() {

    // Image

    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 800;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World

    auto world = scene();

    // Camera

    point3 lookfrom(0,3,10);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 47, aspect_ratio, aperture, dist_to_focus);

    // Render

    std::ofstream fout ("image.ppm");
    fout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(fout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}