/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** main
*/

#include <filesystem>
#include <iostream>
#include "./DLLoader/load_so.hpp"
#include "plugins/renderer/Camera.hpp"
#include "objects/Sphere.hpp"
#include "objects/Plane.hpp"
#include "plugins/renderer/ppm_export.hpp"
#include "math/Point3D.hpp"
#include "utils/Ray.hpp"

void print_help()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "SCENE_FILE: scene configuration" << std::endl;
}

//TODO: - implement the function to parse the JSON scene file and set up the raytracer accordingly
void open_lib_so(std::filesystem::path libPath)
{
    try {
        DLLoader<void> loader(libPath);
        int type = loader.getType();
        std::cout << "Loaded library type: " << type << std::endl;
    } catch (const Exception& e) {
        std::cerr << "Error loading library: " << e.what() << std::endl;
    }
}

bool isJson(char *configFile)
{
    std::string str(configFile);

    if (str.length() < 5 || str.substr(str.length() - 5) != ".json") {
        return false;
    }

    return true;
}

void temp_draw_sphere() {
    RayTracer::Camera cam;
    RayTracer::Sphere s(Math::Point3D(0, 0, -1), 0.5);
    const int image_width = 50;
    const int image_height = 25;
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            double u = static_cast<double>(i) / (image_width - 1);
            double v = static_cast<double>(j) / (image_height - 1);
            RayTracer::Ray r = cam.ray(u, v);
            if (s.hits(r)) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

void temp_draw_plane() {
    RayTracer::Camera cam;
    RayTracer::Plane p(Math::Point3D(0, 0, -1), Math::Vector3D(0, 1, 0));
    const int image_width = 50;
    const int image_height = 25;
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            double u = static_cast<double>(i) / (image_width - 1);
            double v = static_cast<double>(j) / (image_height - 1);
            RayTracer::Ray r = cam.ray(u, v);
            if (p.hits(r)) {
                std::cout << "@"; //@ for the floor
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

void temp_draw_scene() {
    RayTracer::Camera cam;
    RayTracer::Sphere s(Math::Point3D(0, 0, -1), 0.5);
    RayTracer::Plane p(Math::Point3D(0, 1, 0), Math::Vector3D(0, 1, 0));
    const int image_width = 800;
    const int image_height = 600;
    std::vector<std::vector<Math::Vector3D>> pixels(image_height, std::vector<Math::Vector3D>(image_width));
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            double u = static_cast<double>(i) / (image_width - 1);
            double v = static_cast<double>(j) / (image_height - 1);
            RayTracer::Ray r = cam.ray(u, v);
            bool hit_sphere = s.hits(r);
            bool hit_plane = p.hits(r);
            if (hit_sphere && hit_plane) {
                pixels[j][i] = Math::Vector3D(255, 0, 255); // magenta
            } else if (hit_sphere) {
                pixels[j][i] = Math::Vector3D(255, 0, 0); // rouge
            } else if (hit_plane) {
                pixels[j][i] = Math::Vector3D(0, 255, 0); // vert
            } else {
                pixels[j][i] = Math::Vector3D(0, 0, 0); // noir
            }
        }
    }
    PPMExporter exporter;
    exporter.write_image(image_width, image_height, pixels);
}

int main(int argc, char **argv)
{
    try {
        if (argc != 2) {
            print_help();
            return 84;
        }

        if (isJson(argv[1]) == true) {
            // call la fonction
        }

        //open_lib_so(std::filesystem::path(argv[1]));
        temp_draw_scene();
        return 0;
    } catch (const WarningException& e) {
        std::cerr << "WarningException in main: " << e.what() << std::endl;
        return 84;
    } catch (const ErrorException& e) {
        std::cerr << "ErrorException in main: " << e.what() << std::endl;
        return 84;
    } catch (const CrashException& e) {
        std::cerr << "CrashException in main: " << e.what() << std::endl;
        return 84;
    } catch (const Exception& e) {
        std::cerr << "Exception in main: " << e.what() << std::endl;
        return 84;
    }
}