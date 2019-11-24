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
#include <stdlib.h>
#include <functional>

std::random_device rd;
std::default_random_engine gen(rd());
std::uniform_real_distribution<float> unit_dist(0.0,1.0);
auto rand_unit = std::bind(unit_dist, gen);

// get random point in unit cube, reject if not within the unit sphere;
vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        // gen random p in [range(-1,1), range(-1,1), range(-1,1)]
        p = 2.0 * vec3(rand_unit(), rand_unit(), rand_unit()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}

/**
 * Outputs a color modelling diffuse materials
 * If r hits a hitable, reflect in a random direction (absorbing half the light each bounce)
 * If r hits the background, returns a blend of white / blue,
 * depending on the y value of the input ray
 */
vec3 color(const ray& r, hitable* world) {
    hit_record rec;
    // t_min=0.001 to disallow self_hits (removes shadow acne)
    if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5*color(ray(rec.p, target-rec.p), world);
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

    // shoot rays starting from lower left corner,
    // then traverse screen from bottom to top, left to right
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);

            // antialiasing: sample s times for each pixel
            for (int s=0; s < ns; s++) {
                float u = float(i + rand_unit()) / float(nx);
                float v = float(j + rand_unit()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(ns);
            // apply gamma correction
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            printf("%i %i %i\n", ir, ig, ib);
        }
    }
}