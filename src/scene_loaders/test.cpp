/*
** EPITECH PROJECT, 2026
** test
** File description:
** test de link le parsing avec le bootstrap
*/

#include "config/test.hpp"
#include "objects/Sphere.hpp"
#include "./utils/Ray.hpp"
#include "objects/Plane.hpp"

Raytracer::test::test(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights) : _primitive(primitive), _camera(camera), _lights(lights), _cam(camera.size.first, camera.size.second) 
{
}

Raytracer::test::~test()
{
}

void Raytracer::test::drawSphere()
{
    Raytracer::Sphere s(Math::Point3D(0, 0, -1), 0.5);

    for (int j = 0; j < _camera.size.second; ++j) {
        for (int i = 0; i < _camera.size.first; ++i) {
            double u = static_cast<double>(i) / (_camera.size.first - 1);
            double v = static_cast<double>(j) / (_camera.size.second - 1);
            Raytracer::Ray r = _cam.ray(u, v);
            if (s.hits(r)) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

void Raytracer::test::drawPlane() {
    Raytracer::PlaneClass p(Math::Point3D(0, 0, -1), Math::Vector3D(0, 1, 0)); // fais 
    for (int j = 0; j < _camera.size.second; ++j) {
        for (int i = 0; i < _camera.size.first; ++i) {
            double u = static_cast<double>(i) / (_camera.size.first - 1);
            double v = static_cast<double>(j) / (_camera.size.second - 1);
            Raytracer::Ray r = _cam.ray(u, v);
            if (p.hits(r)) {
                std::cout << "@"; //@ for the floor
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

void Raytracer::test::createScene()
{
    drawPlane();
    drawSphere();
    // for (auto &shape : _primitive.listOfShapes) {
    //     // call la factory avec le type
    // }

    // for (auto &plane : _primitive.listOfPlane) {
    //     // call la factory avec le plane
    // }

}


// void temp_draw_scene() {
//     std::vector<std::vector<Math::Vector3D>> pixels(image_height, std::vector<Math::Vector3D>(image_width));
//     for (int j = 0; j < image_height; ++j) {
//         for (int i = 0; i < image_width; ++i) {
//             double u = static_cast<double>(i) / (image_width - 1);
//             double v = static_cast<double>(j) / (image_height - 1);
//             Raytracer::Ray r = cam.ray(u, v);
//             bool hit_sphere = s.hits(r);
//             bool hit_plane = p.hits(r);
//             if (hit_sphere && hit_plane) {
//                 pixels[j][i] = Math::Vector3D(255, 0, 255); // magenta
//             } else if (hit_sphere) {
//                 pixels[j][i] = Math::Vector3D(255, 0, 0); // rouge
//             } else if (hit_plane) {
//                 pixels[j][i] = Math::Vector3D(0, 255, 0); // vert
//             } else {
//                 pixels[j][i] = Math::Vector3D(0, 0, 0); // noir
//             }
//         }
//     }
//     PPMExporter exporter;
//     exporter.write_image(image_width, image_height, pixels);
// }