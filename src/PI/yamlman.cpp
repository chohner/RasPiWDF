#include "yamlman.h"

YamlMan::YamlMan()
{

    YAML::Node config = YAML::LoadFile("config.yml");


    int port = config["length"].as<int>();

    std::cout  << port << std::endl;

}

