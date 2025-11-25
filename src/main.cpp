#include <chrono>

#include "utils/common.h"
#include "world/camera.h"
#include "world/hittable_list.h"

// include objects
#include "objects/cone.h"
#include "objects/cube.h"
#include "objects/cylinder.h"
#include "objects/hittable.h"
#include "objects/plane.h"
#include "objects/sphere.h"
#include "objects/triangle.h"

// include materials
#include "materials/metal.h"
#include "materials/lambertian.h"
#include "materials/dielectric.h"

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    // Materials
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_center2 = make_shared<lambertian>(color(0.1, 0.5, 0.2));
    auto material_triangle = make_shared<lambertian>(color(0.5, 0.2, 0.1));
    auto material_left = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1);

    // World
    hittable_list world;

    world.add(make_shared<plane>(point3(0, -0.5, 0), point3(0, 0, 0), point3(100, 1, 100), material_ground));
    world.add(make_shared<cube>(point3(0, 0, -1.2), point3(pi / 4, -pi / 4, pi / 4), point3(1, 0.5, 0.5), material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
    world.add(make_shared<cone>(point3(1.2, -0.3, -1), point3(-pi / 18 * 1.5, pi / 32, -pi / 18 * 2.5), point3(1, 1.5, 1), 16, material_right));
    world.add(make_shared<cylinder>(point3(0.5, -0.45, -0.7), point3(0, pi / 32, 0), point3(0.7, 0.1, 0.7), 20, material_center2));
    // world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.lookfrom = point3(0, 0.25, 0.25);
    // cam.lookat = point3(0, 0, -1);
    // cam.vup = vec3(0, 1, 0);

    // cam.defocus_angle = 10.0;
    // cam.focus_dist = 3.4;

    cam.render(world);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time elapsed = " << elapsed.count() << " seconds.\n";
}