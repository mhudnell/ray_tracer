#include <iostream>
#include "vec3.h"

int main() {
    int nx = 200;
    int ny = 100;

    printf("P3\n");
    printf("%i %i\n", nx, ny);
    printf("255\n");

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            // r goes from 0->1 from left to right
            // g goes from 1->0 from top to bottom
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            vec3 col(r, g, b);

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            printf("%i %i %i\n", ir, ig, ib);
        }
    }
}