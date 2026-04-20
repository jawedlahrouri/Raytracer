#include "plugins/renderer/Camera.hpp"
#include "exception.hpp"
#include <iostream>

namespace RayTracer {
    Camera::~Camera() {
        try {
            // Destruction normale
        } catch (const CrashException& e) {
            std::cerr << "CrashException in Camera::~Camera: " << e.what() << std::endl;
        } catch (const ErrorException& e) {
            std::cerr << "ErrorException in Camera::~Camera: " << e.what() << std::endl;
        } catch (const WarningException& e) {
            std::cerr << "WarningException in Camera::~Camera: " << e.what() << std::endl;
        } catch (const Exception& e) {
            std::cerr << "Exception in Camera::~Camera: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception in Camera::~Camera" << std::endl;
        }
    }
}
