#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "../utils/vec3.h"
#include "hittable.h"

class triangle : public hittable
{
public:
    triangle(const point3 &A, const point3 &B, const point3 &C, shared_ptr<material> mat)
        : A(A), B(B), C(C), mat(mat) {}

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        const double EPS = 1e-6;
        vec3 E1 = B - A;
        vec3 E2 = C - A;

        vec3 P = cross(r.direction(), E2);
        double det = dot(E1, P);
        // if ray is almost parallel to place
        if (std::fabs(det) < EPS)
            return false;
        double invDet = 1.0 / det;

        vec3 T = r.origin() - A;
        double u = dot(T, P) * invDet;
        if (u < 0.0 || u > 1.0)
            return false;

        vec3 Q = cross(T, E1);
        double v = dot(r.direction(), Q) * invDet;
        if (v < 0.0 || (u + v) > 1.0)
            return false;

        double t = dot(E2, Q) * invDet;
        if (!ray_t.surrounds(t))
            return false;

        rec.t = t;
        rec.p = r.at(rec.t);
        vec3 outward_normal = unit_vector(cross(E1, E2));
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }

private:
    point3 A, B, C;
    shared_ptr<material> mat;
};
#endif