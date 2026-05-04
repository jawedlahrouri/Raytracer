/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** main
*/

#include <filesystem>
#include <iostream>
#include "./parsing.hpp"
#include "./DLLoader/load_so.hpp"
#include "plugins/renderer/Camera.hpp"
#include "plugins/renderer/ppm_export.hpp"
#include "math/Point3D.hpp"
#include "utils/Ray.hpp"
#include "config/test.hpp"
#include "utils/HitRecord.hpp"
#include "plugins/lights/PointLight.hpp"
#include "plugins/renderer/Shadow_Ray.hpp"
#include "spacePartitionning/BVH.hpp"
#include "display/sfml_display.hpp"

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

bool isJson(const std::string& configFile)
{
    if (configFile.length() < 5)
        return false;
    if (configFile.substr(configFile.length() - 5) == ".json")
        return true;
    return false;
}

int runRaytracer(const std::string& configFile, bool useDisplay)
{
    Raytracer::Parser parser(configFile);
    if (parser.parser() != 0)
        return 84;

    Raytracer::test test(parser.getInfoPrimitive(), parser.getInfoCamera(), parser.getInfoLights());
    Raytracer::ObjectFactory factory;
    Raytracer::BVH bvh;

    if (useDisplay) {
        Raytracer::SfmlDisplay display(
            static_cast<int>(parser.getInfoCamera().size.first), 
            static_cast<int>(parser.getInfoCamera().size.second), 
            "Raytracer"
        );
        test.createScene(bvh, factory, &display);
        while (display.isOpen()) {
            display.refresh();
        }
    } else {
        test.createScene(bvh, factory);
    }
    return 0;
}

int main(int argc, char **argv)
{
    try {
        if (argc < 2) {
            print_help();
            return 84;
        }
        std::string firstArg = argv[1];
        if (firstArg == "--help") {
            print_help();
            return 0;
        }
        if (!isJson(firstArg)) {
            throw ErrorException("Le fichier n'est pas un .json");
        }

        bool useDisplay = (argc == 3 && std::string(argv[2]) == "--display");
        return runRaytracer(firstArg, useDisplay);
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
    return 0;
}