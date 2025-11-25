#ifndef CUBE_H
#define CUBE_H
#include "../utils/vec3.h"
#include "hittable.h"
#include "triangle.h"

class cube : public hittable
{
public:
    // rot must be in radians
    cube(const point3 &loc, const vec3 &rot, const vec3 &scale, std::shared_ptr<material> mat) : mat(mat)
    {
        build(loc, rot, scale, mat);
    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto &object : tris)
        {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }

    const std::vector<std::shared_ptr<triangle>> &triangles() const { return tris; }

private:
    std::vector<std::shared_ptr<triangle>> tris;
    shared_ptr<material> mat;

    void build(const point3 &loc, const vec3 &rot, const vec3 &scale, std::shared_ptr<material> mat)
    {
        // base unit cube centered at origin (-0.5..+0.5)
        std::vector<vec3> base = {
            vec3(-0.5, -0.5, -0.5),
            vec3(0.5, -0.5, -0.5),
            vec3(0.5, 0.5, -0.5),
            vec3(-0.5, 0.5, -0.5),
            vec3(-0.5, -0.5, 0.5),
            vec3(0.5, -0.5, 0.5),
            vec3(0.5, 0.5, 0.5),
            vec3(-0.5, 0.5, 0.5)};

        // transform vertices: S > R > T
        std::vector<point3> v(8);
        for (int i = 0; i < 8; ++i)
        {
            vec3 p = vec3(base[i].x() * scale.x(), base[i].y() * scale.y(), base[i].z() * scale.z());
            p = rotate_euler(p, rot);
            p = p + loc;
            v[i] = p;
        }

        // 12 triangles (CCW winding) two per face
        static const int t[12][3] = {
            // -Z face (back)
            {0, 1, 2},
            {0, 2, 3},
            // +Z face (front)
            {4, 6, 5},
            {4, 7, 6},
            // -Y face (bottom)
            {0, 5, 1},
            {0, 4, 5},
            // +Y face (top)
            {3, 2, 6},
            {3, 6, 7},
            // -X face (left)
            {0, 3, 7},
            {0, 7, 4},
            // +X face (right)
            {1, 5, 6},
            {1, 6, 2}};

        tris.clear();
        tris.reserve(12);
        for (int i = 0; i < 12; ++i)
        {
            point3 A = v[t[i][0]];
            point3 B = v[t[i][1]];
            point3 C = v[t[i][2]];
            tris.push_back(std::make_shared<triangle>(A, B, C, mat));
        }
    }
};
#endif