/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Ray
*/

#include "utils/Ray.hpp"
#include "exception.hpp"
#include "math/Point3D.hpp"
#include <iostream>

namespace Raytracer {
    Ray::Ray(const Math::Point3D& origin, const Math::Vector3D& direction) : origin(origin), direction(direction) {
        try {
            // Construction normale
        } catch (const WarningException& e) {
            std::cerr << "WarningException in Ray::Ray: " << e.what() << std::endl;
        } catch (const ErrorException& e) {
            std::cerr << "ErrorException in Ray::Ray: " << e.what() << std::endl;
        } catch (const CrashException& e) {
            std::cerr << "CrashException in Ray::Ray: " << e.what() << std::endl;
        } catch (const Exception& e) {
            std::cerr << "Exception in Ray::Ray: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception in Ray::Ray" << std::endl;
        }
    }
    Ray::~Ray() {
        try {
            // Destruction normale
        } catch (const WarningException& e) {
            std::cerr << "WarningException in Ray::~Ray: " << e.what() << std::endl;
        } catch (const ErrorException& e) {
            std::cerr << "ErrorException in Ray::~Ray: " << e.what() << std::endl;
        } catch (const CrashException& e) {
            std::cerr << "CrashException in Ray::~Ray: " << e.what() << std::endl;
        } catch (const Exception& e) {
            std::cerr << "Exception in Ray::~Ray: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception in Ray::~Ray" << std::endl;
        }
    }
}
