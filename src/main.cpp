/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** main
*/

#include <filesystem>
#include <iostream>
#include "../include/parsing.hpp"
#include "./DLLoader/load_so.hpp"
#include "plugins/renderer/Camera.hpp"
#include "plugins/renderer/ppm_export.hpp"
#include "math/Point3D.hpp"
#include "utils/Ray.hpp"
#include "config/test.hpp"
#include "utils/HitRecord.hpp"
#include "plugins/lights/PointLight.hpp"
#include "plugins/renderer/Shadow_Ray.hpp"

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

int main(int argc, char **argv)
{
    try {
        if (argc != 2) {
            print_help();
            return 84;
        }

        if (isJson(argv[1]) == false) {
            throw ErrorException("Le fichier n'est pas un .json");
        }

        Raytracer::Parser parser(argv[1]);
        parser.parser();

        Raytracer::test test(parser.getInfoPrimitive(), parser.getInfoCamera(), parser.getInfoLights());
        test.createScene();

        //open_lib_so(std::filesystem::path(argv[1]));
        // temp_draw_scene();
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
    return 0;
}