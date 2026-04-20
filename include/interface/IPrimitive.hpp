/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_

class IPrimitive {
    public:
        IPrimitive();
        ~IPrimitive();

        // Check if the ray intersects with the primitive and fill the hit record if it does
        virtual bool intersect(const Ray& ray, float t_min, float t_max, HitRecord& record) const = 0;

    protected:
    private:
};

#endif /* !IPRIMITIVE_HPP_ */
