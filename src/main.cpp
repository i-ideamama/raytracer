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

// world prototypes
hittable_list debug_world();
hittable_list main_world();

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    // World
    hittable_list world = debug_world();
    // hittable_list world = main_world();

    // Camera
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    // cam.lookfrom = point3(2, 1.5, 1.5);
    // cam.lookat = point3(0.5, 1.25, -0.5);
    // cam.lookfrom = point3(0.5, 1.75, 0.6);
    // cam.lookat = point3(0.5, 1.7, 0);
    // cam.vup = vec3(0, 1, 0);

    // cam.defocus_angle = 4.0;
    // cam.focus_dist = 0.75;
    // cam.vfov = 60;
    // cam.vfov = 75;

    cam.render(world);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::clog << "Time elapsed = " << elapsed.count() << " seconds.\n"
              << std::flush;
}

hittable_list main_world()
{
    // Materials
    auto debug = make_shared<lambertian>(color(0.7, 0.7, 0.7));
    auto cone_mat = make_shared<lambertian>(color(0.1, 0.1, 0.1));
    auto floor_mat = make_shared<lambertian>(color(0.094, 0.094, 0.094));
    auto wall_mat = make_shared<lambertian>(color(0.008, 0.188, 0.125));
    auto wood_mat = make_shared<lambertian>(color(0.702, 0.373, 0.09));
    auto dark_wood_mat = make_shared<lambertian>(color(0.569, 0.302, 0.071));
    auto metal_mat = make_shared<metal>(color(0.9, 0.9, 0.9), 0.15);
    auto cone_metal_mat = make_shared<metal>(color(0.5, 0.5, 0.5), 0.15);
    auto glass_mat = make_shared<dielectric>(1.50);
    auto air_mat = make_shared<dielectric>(1.00 / 1.50);

    // Objects
    hittable_list world;

    // Planes
    auto back_plane = make_shared<plane>(point3(1.5, 3.25, -3.5), point3(pi / 2, 0, 0), point3(7.5, 1, 7.5), wall_mat);
    auto floor = make_shared<plane>(point3(0, 0, 0), point3(0, 0, 0), point3(20, 1, 20), floor_mat);
    auto left_plane_1 = make_shared<plane>(point3(-1.5, 3, 2), point3(0, 0, -pi / 2), point3(6.5, 1, 3), wall_mat);
    auto left_plane_2 = make_shared<plane>(point3(-1.5, 3, -2.5), point3(0, 0, -pi / 2), point3(7.5, 1, 3.5), wall_mat);
    auto left_plane_3 = make_shared<plane>(point3(-1.5, 0.75, -0.25), point3(0, 0, -pi / 2), point3(2.5, 1, 2), wall_mat);
    auto left_plane_4 = make_shared<plane>(point3(-1.5, 5.25, -0.25), point3(0, 0, -pi / 2), point3(2, 1, 2), wall_mat);

    // Cubes
    auto back_rest = make_shared<cube>(point3(0.5, 1.9, -1.25), point3(-pi / 18, 0, 0), point3(1.2, 1.6, 0.1), wood_mat);
    auto left_arm_rest = make_shared<cube>(point3(1.1, 1.6, -0.6), point3(0, 0, 0), point3(0.15, 0.1, 1.4), dark_wood_mat);
    auto right_arm_rest = make_shared<cube>(point3(-0.1, 1.6, -0.6), point3(0, 0, 0), point3(0.15, 0.1, 1.4), dark_wood_mat);
    auto left_arm_rest_supp = make_shared<cube>(point3(1.1, 1.375, -0.05), point3(0, 0, 0), point3(0.05, 0.4, 0.15), dark_wood_mat);
    auto right_arm_rest_supp = make_shared<cube>(point3(-0.1, 1.375, -0.05), point3(0, 0, 0), point3(0.05, 0.4, 0.15), dark_wood_mat);
    auto seat = make_shared<cube>(point3(0.5, 1.1, -0.5), point3(0, 0, 0), point3(1.4, 0.15, 1.4), wood_mat);

    // Cylinders
    auto leg_1 = make_shared<cylinder>(point3(0, 0.5, 0), point3(-pi / 18 * 1.5, 0, 0), point3(0.1, 1.1, 0.1), 16, metal_mat);
    auto leg_2 = make_shared<cylinder>(point3(1, 0.5, 0), point3(-pi / 18 * 1.5, 0, 0), point3(0.1, 1.1, 0.1), 16, metal_mat);
    auto leg_3 = make_shared<cylinder>(point3(1, 0.5, -1), point3(pi / 18 * 1.5, 0, 0), point3(0.1, 1.1, 0.1), 16, metal_mat);
    auto leg_4 = make_shared<cylinder>(point3(0, 0.5, -1), point3(pi / 18 * 1.5, 0, 0), point3(0.1, 1.1, 0.1), 16, metal_mat);

    // Other Shapes
    auto cone_obj = make_shared<cone>(point3(0.7, 1, -0.7), point3(0, 0, 0), point3(0.75, 1, 0.75), 16, cone_metal_mat);
    auto sphere_obj = make_shared<sphere>(point3(0.3, 1.475, -0.25), 0.3, glass_mat);
    auto inner_sphere_obj = make_shared<sphere>(point3(0.3, 1.475, -0.3), 0.25, air_mat);

    world.add(back_plane);
    world.add(floor);
    world.add(left_plane_1);
    world.add(left_plane_2);
    world.add(left_plane_3);
    world.add(left_plane_4);

    world.add(back_rest);
    world.add(left_arm_rest);
    world.add(right_arm_rest);
    world.add(left_arm_rest_supp);
    world.add(right_arm_rest_supp);
    world.add(seat);

    world.add(leg_1);
    world.add(leg_2);
    world.add(leg_3);
    world.add(leg_4);

    world.add(cone_obj);
    world.add(sphere_obj);
    world.add(inner_sphere_obj);

    return world;
}

hittable_list debug_world()
{
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

    return world;
}