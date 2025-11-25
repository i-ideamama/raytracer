#ifndef CYLINDER_H
#define CYLINDER_H
#include "../utils/vec3.h"
#include "hittable.h"
#include "triangle.h"

class cylinder : public hittable
{
public:
    // rot must be in radians
    cylinder(const point3 &loc, const vec3 &rot, const vec3 &scale, int divisions, std::shared_ptr<material> mat) : mat(mat)
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

    std::vector<vec3> make_cylinder(int n)
    {
        std::vector<vec3> verts;
        // top circle (n) + bottom circle (n) + 2 centers
        verts.reserve(2 * n + 2);
        float radius = 0.5f;
        float y_bottom = -0.5f;
        float y_top = 0.5f;

        // Top circle
        for (int i = 0; i < n; i++)
        {
            float angle = (2.0f * M_PI * i) / n;
            float x = radius * std::cos(angle);
            float z = radius * std::sin(angle);
            verts.push_back(vec3(x, y_top, z));
        }
        // Bottom circle
        for (int i = 0; i < n; i++)
        {
            float angle = (2.0f * M_PI * i) / n;
            float x = radius * std::cos(angle);
            float z = radius * std::sin(angle);
            verts.push_back(vec3(x, y_bottom, z));
        }
        // Top center
        verts.push_back(vec3(0.0f, y_top, 0.0f));
        // Bottom center
        verts.push_back(vec3(0.0f, y_bottom, 0.0f));
        return verts;
    }

    std::vector<std::vector<int>> make_cone_triangles(int n)
    {
        // 2 per division for sides, + n for top cap, + n for bottom cap
        // 4n total
        std::vector<std::vector<int>> tri_list;
        tri_list.reserve(4 * n);

        // side faces (two triangles per division)
        for (int i = 0; i < n; i++)
        {
            int next = (i + 1) % n;

            int top_i = i;           // 0 .. n-1
            int top_next = next;     // 0 .. n-1
            int bot_i = i + n;       // n .. 2n-1
            int bot_next = next + n; // n .. 2n-1

            tri_list.push_back({top_i, bot_i, top_next});
            tri_list.push_back({top_next, bot_i, bot_next});
        }

        // top cap
        int top_center = 2 * n;
        for (int i = 0; i < n; i++)
        {
            int next = (i + 1) % n;
            tri_list.push_back({top_center, i, next});
        }
        // bottom cap
        int bot_center = 2 * n + 1;
        for (int i = 0; i < n; i++)
        {
            int next = (i + 1) % n;
            int bot_i = i + n;
            int bot_next = next + n;
            tri_list.push_back({bot_center, bot_next, bot_i});
        }

        return tri_list;
    }

    void build(const point3 &loc, const vec3 &rot, const vec3 &scale, int divisions, std::shared_ptr<material> mat)
    {
        std::vector<vec3> base = make_cylinder(divisions);

        // transform vertices: S > R > T
        std::vector<point3> v(2 * divisions + 2);
        for (int i = 0; i < 2 * divisions + 2; ++i)
        {
            vec3 p = vec3(base[i].x() * scale.x(), base[i].y() * scale.y(), base[i].z() * scale.z());
            p = rotate_euler(p, rot);
            p = p + loc;
            v[i] = p;
        }

        // 4 * divisions triangles
        std::vector<std::vector<int>> t = make_cone_triangles(divisions);

        tris.clear();
        tris.reserve(4 * divisions);
        for (int i = 0; i < 4 * divisions; ++i)
        {
            point3 A = v[t[i][0]];
            point3 B = v[t[i][1]];
            point3 C = v[t[i][2]];
            tris.push_back(std::make_shared<triangle>(A, B, C, mat));
        }
    }
};
#endif