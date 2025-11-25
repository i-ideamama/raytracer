#ifndef CONE_H
#define CONE_H
#include "../utils/vec3.h"
#include "hittable.h"
#include "triangle.h"

class cone : public hittable
{
public:
    // rot must be in radians
    cone(const point3 &loc, const vec3 &rot, const vec3 &scale, int divisions, std::shared_ptr<material> mat) : mat(mat)
    {
        build(loc, rot, scale, divisions, mat);
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

    std::vector<vec3> make_cone(int n)
    {
        std::vector<vec3> verts;
        verts.reserve(n + 1);
        float radius = 0.5f;
        float y_base = 0.0f;
        float y_tip = 1.0f;
        verts.push_back(vec3(0.0f, y_tip, 0.0f));

        // Base circle vertices
        for (int i = 0; i < n; i++)
        {
            float angle = (2.0f * M_PI * i) / n;
            float x = radius * std::cos(angle);
            float z = radius * std::sin(angle);
            verts.push_back(vec3(x, y_base, z));
        }

        return verts;
    }

    std::vector<std::vector<int>> make_cone_triangles(int n)
    {
        std::vector<std::vector<int>> tri_list;
        tri_list.reserve(2 * n - 1);

        // slant faces
        for (int i = 1; i <= n; i++)
        {
            int next = (i % n) + 1; // wrap last to 1
            tri_list.push_back({0, i, next});
        }
        // bottom faces
        for (int i = 2; i <= n; i++)
        {
            int next = (i % n) + 1; // wraps final segment
            tri_list.push_back({1, next, i});
        }

        return tri_list;
    }

    void build(const point3 &loc, const vec3 &rot, const vec3 &scale, int divisions, std::shared_ptr<material> mat)
    {
        std::vector<vec3> base = make_cone(divisions);

        // transform vertices: S > R > T
        std::vector<point3> v(divisions + 1);
        for (int i = 0; i < divisions + 1; ++i)
        {
            vec3 p = vec3(base[i].x() * scale.x(), base[i].y() * scale.y(), base[i].z() * scale.z());
            p = rotate_euler(p, rot);
            p = p + loc;
            v[i] = p;
        }

        // 2 * divisions - 1 triangles
        std::vector<std::vector<int>> t = make_cone_triangles(divisions);

        tris.clear();
        tris.reserve(2 * divisions - 1);
        for (int i = 0; i < 2 * divisions - 1; ++i)
        {
            point3 A = v[t[i][0]];
            point3 B = v[t[i][1]];
            point3 C = v[t[i][2]];
            tris.push_back(std::make_shared<triangle>(A, B, C, mat));
        }
    }
};
#endif