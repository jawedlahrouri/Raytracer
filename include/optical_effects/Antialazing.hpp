#ifndef ANTIALAZING_HPP_
#define ANTIALAZING_HPP_

#include "math/Vector3D.hpp"
#include <functional>

namespace Raytracer {
    class Antialazing {
        public:
            static Math::Vector3D resolvePixel(
                int i,
                int j,
                int width,
                int height,
                int aaLevel,
                double aaThreshold,
                std::function<Math::Vector3D(double, double)> computeColor
            );

        private:
            struct Bounds {
                double u_min, v_min, u_max, v_max;
            };

            static Math::Vector3D simpleSampling(int i, int j, int width, int height, std::function<Math::Vector3D(double, double)> computeColor);
            static Bounds getPixelBounds(int i, int j, int width, int height);
            static double colorDiff(const Math::Vector3D& a, const Math::Vector3D& b);
            static double calculateMaxVariance(const Math::Vector3D& c1, const Math::Vector3D& c2, const Math::Vector3D& c3, const Math::Vector3D& c4, const Math::Vector3D& c_center);
            static Math::Vector3D deepSampling(const Bounds& bounds, int aaLevel, std::function<Math::Vector3D(double, double)> computeColor);
    };
}

#endif /* !ANTIALAZING_HPP_ */
