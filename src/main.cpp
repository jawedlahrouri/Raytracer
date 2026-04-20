/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** main
*/

#include <iostream>

void print_help()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "SCENE_FILE: scene configuration" << std::endl;
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
    if (argc != 2)
    {
        print_help();
        return 84;
    }
    if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"){
        print_help();
        return 0;
    }

    if (isJson(argv[1]) == true) {
        // call la fonction
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}