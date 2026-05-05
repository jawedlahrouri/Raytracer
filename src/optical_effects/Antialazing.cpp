#include "optical_effects/Antialazing.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

namespace Raytracer {
    Math::Vector3D Antialazing::resolvePixel(
        int i,
        int j,
        int width,
        int height,
        int aaLevel,
        double aaThreshold,
        std::function<Math::Vector3D(double, double)> computeColor
    ) {
        if (aaLevel <= 0)
            return simpleSampling(i, j, width, height, computeColor);

        Bounds bounds = getPixelBounds(i, j, width, height);
        
        Math::Vector3D c1 = computeColor(bounds.u_min, bounds.v_min);
        Math::Vector3D c2 = computeColor(bounds.u_max, bounds.v_min);
        Math::Vector3D c3 = computeColor(bounds.u_min, bounds.v_max);
        Math::Vector3D c4 = computeColor(bounds.u_max, bounds.v_max);
        Math::Vector3D c_center = computeColor(bounds.u_min + (bounds.u_max - bounds.u_min) / 2.0, 
                                            bounds.v_min + (bounds.v_max - bounds.v_min) / 2.0);

        if (calculateMaxVariance(c1, c2, c3, c4, c_center) < aaThreshold) {
            return (c1 + c2 + c3 + c4 + c_center) / 5.0;
        }
        return deepSampling(bounds, aaLevel, computeColor);
    }

    Math::Vector3D Antialazing::simpleSampling(int i, int j, int width, int height, std::function<Math::Vector3D(double, double)> computeColor) {
        return computeColor(static_cast<double>(i) / (width - 1), static_cast<double>(j) / (height - 1));
    }

    Antialazing::Bounds Antialazing::getPixelBounds(int i, int j, int width, int height) {
        return {
            static_cast<double>(i) / (width - 1),
            static_cast<double>(j) / (height - 1),
            static_cast<double>(i + 1) / (width - 1),
            static_cast<double>(j + 1) / (height - 1)
        };
    }

    double Antialazing::colorDiff(const Math::Vector3D& a, const Math::Vector3D& b) {
        return std::abs(a.X - b.X) + std::abs(a.Y - b.Y) + std::abs(a.Z - b.Z);
    }

    double Antialazing::calculateMaxVariance(const Math::Vector3D& c1, const Math::Vector3D& c2, const Math::Vector3D& c3, const Math::Vector3D& c4, const Math::Vector3D& c_center) {
        return std::max({
            colorDiff(c1, c_center), colorDiff(c2, c_center),
            colorDiff(c3, c_center), colorDiff(c4, c_center)
        });
    }

    Math::Vector3D Antialazing::deepSampling(const Bounds& bounds, int aaLevel, std::function<Math::Vector3D(double, double)> computeColor) {
        Math::Vector3D deep_color(0, 0, 0);
        for (int x = 0; x < aaLevel; ++x) {
            for (int y = 0; y < aaLevel; ++y) {
                double u = bounds.u_min + ((static_cast<double>(x) + 0.5) / aaLevel) * (bounds.u_max - bounds.u_min);
                double v = bounds.v_min + ((static_cast<double>(y) + 0.5) / aaLevel) * (bounds.v_max - bounds.v_min);
                deep_color = deep_color + computeColor(u, v);
            }
        }
        return deep_color / static_cast<double>(aaLevel * aaLevel);
    }
}
