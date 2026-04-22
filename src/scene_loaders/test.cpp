/*
** EPITECH PROJECT, 2026
** test
** File description:
** test de link le parsing avec le bootstrap
*/

#include "config/test.hpp"

Raytracer::test::test(Raytracer::Primitive primitive, Raytracer::Camera camera, Raytracer::Lights lights) : _primitive(primitive), _camera(camera), _lights(lights)
{
}

Raytracer::test::~test()
{
}

void Raytracer::test::drawShape()
{
    // a faire
}

void Raytracer::test::createScene()
{
    // faire l'appelle a la factory
}

// void temp_draw_sphere() {
//     RayTracer::Camera cam;
//     RayTracer::Sphere s(Math::Point3D(0, 0, -1), 0.5);
//     const int image_width = 50;
//     const int image_height = 25;
//     for (int j = 0; j < image_height; ++j) {
//         for (int i = 0; i < image_width; ++i) {
//             double u = static_cast<double>(i) / (image_width - 1);
//             double v = static_cast<double>(j) / (image_height - 1);
//             RayTracer::Ray r = cam.ray(u, v);
//             if (s.hits(r)) {
//                 std::cout << "#";
//             } else {
//                 std::cout << ".";
//             }
//         }
//         std::cout << std::endl;
//     }
// }

// void temp_draw_plane() {
//     RayTracer::Camera cam;
//     RayTracer::Plane p(Math::Point3D(0, 0, -1), Math::Vector3D(0, 1, 0));
//     const int image_width = 50;
//     const int image_height = 25;
//     for (int j = 0; j < image_height; ++j) {
//         for (int i = 0; i < image_width; ++i) {
//             double u = static_cast<double>(i) / (image_width - 1);
//             double v = static_cast<double>(j) / (image_height - 1);
//             RayTracer::Ray r = cam.ray(u, v);
//             if (p.hits(r)) {
//                 std::cout << "@"; //@ for the floor
//             } else {
//                 std::cout << ".";
//             }
//         }
//         std::cout << std::endl;
//     }
// }

// void temp_draw_scene() {
//     RayTracer::Camera cam;
//     RayTracer::Sphere s(Math::Point3D(0, 0, -1), 0.5);
//     RayTracer::Plane p(Math::Point3D(0, 1, 0), Math::Vector3D(0, 1, 0));
//     const int image_width = 800;
//     const int image_height = 600;
//     std::vector<std::vector<Math::Vector3D>> pixels(image_height, std::vector<Math::Vector3D>(image_width));
//     for (int j = 0; j < image_height; ++j) {
//         for (int i = 0; i < image_width; ++i) {
//             double u = static_cast<double>(i) / (image_width - 1);
//             double v = static_cast<double>(j) / (image_height - 1);
//             RayTracer::Ray r = cam.ray(u, v);
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