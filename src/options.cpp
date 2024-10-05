#include "options.h"
#include <bits/getopt_core.h>
#include <iostream>
#include <unistd.h>

Config get_config(int argc, char **argv){
    Config config;
    config.training = false;
    int opt = 0;
    while( (opt = getopt(argc, argv, CONFIG_PATTERN)) != -1){
        switch(opt){
            case 'w':
                std::cout << "Takes weights from file:" << optarg << "\n";
                break;
            case 'a':
                config.training = true;
                break;
            case 't':
                config.text = optarg;
                break;
            case 'g':
                config.group_name= optarg;
                break;
            default:
                std::cout << "Wrong parameter! " << optarg << "\n";
                break;
        }
    }
    return config;
}
