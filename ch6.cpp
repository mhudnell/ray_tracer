#include <iostream>
#include <vector>
#include <limits>
#include <random>
#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"
#include "hitable.h"
#include "sphere.h"
#include "camera.h"

/**
 * Outputs a color 
 * If r hits a hitable, convert the surface normal to a color
 * If r hits the background, returns a blend of white / blue,
 * depending on the y value of the input ray
 */
vec3 color(const ray& r, hitable* world) {
    hit_record rec;
    if (world->hit(r, 0.0, std::numeric_limits<float>::max(), rec)) {
        vec3& N = rec.normal;
        // convert [-1,1] scale to [0,1] so we can use it for rgb colors
        return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
    } else {
        vec3 unit_direction = unit_vector(r.direction());  // -1.0 < y < 1.0
        float t = 0.5*(unit_direction.y() + 1.0);  // 0.0 < t < 1.0

        vec3 white(1.0, 1.0, 1.0);  // when t = 0, should be white
        vec3 blue(0.5, 0.7, 1.0);  // when t = 1, should be blue

        return (1.0-t)*white + t*blue;  // linear interpolation (lerp)
    }
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100;

    // create a list of spheres to hit
    std::vector<hitable*> list;
    list.push_back(new sphere(vec3(0,0,-1), 0.5));
    list.push_back(new sphere(vec3(0,-100.5,-1), 100));
    hitable_list* world = new hitable_list(list);

    // print ppm header info
    printf("P3\n");
    printf("%i %i\n", nx, ny);
    printf("255\n");

    camera cam;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0,1.0);
    // shoot rays starting from lower left corner,
    // then traverse screen from bottom to top, left to right
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);

            // antialiasing: sample s times for each pixel
            for (int s=0; s < ns; s++) {
                float u = float(i + distribution(generator)) / float(nx);
                float v = float(j + distribution(generator)) / float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world);
            }
            col /= float(ns);

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            printf("%i %i %i\n", ir, ig, ib);
        }
    }
}