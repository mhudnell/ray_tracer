#include <iostream>
#include "vec3.h"
#include "ray.h"

// returns true if ray r hits sphere with given center / radius
bool hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(r.direction(), oc);
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

/**
 * Outputs a color 
 * If r hits the specified sphere, returns red
 * If r hits the background, returns a blend of white / blue,
 * depending on the y value of the input ray
 */
vec3 color(const ray& r) {
    if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {
        return vec3(1, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());  // -1.0 < y < 1.0
    float t = 0.5*(unit_direction.y() + 1.0);  // 0.0 < t < 1.0

    vec3 white(1.0, 1.0, 1.0);  // when t = 0, should be white
    vec3 blue(0.5, 0.7, 1.0);  // when t = 1, should be blue

    return (1.0-t)*white + t*blue;  // linear interpolation (lerp)
}

int main() {
    int nx = 200;
    int ny = 100;

    printf("P3\n");
    printf("%i %i\n", nx, ny);
    printf("255\n");

    // choice of (-2,-1,-1) seems arbitrary, but makes sense with 200px x 100px
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    // shoot rays starting from lower left corner,
    // then traverse screen from bottom to top, left to right
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            printf("%i %i %i\n", ir, ig, ib);
        }
    }
}