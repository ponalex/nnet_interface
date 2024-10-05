#include <vector>


//   w files with weights
//   a train a model
//   file with a text
//   file with a group ID
#define CONFIG_PATTERN "w:at:g:"


#include <string>
typedef struct Config{
    std::vector<std::string> weights_file;
    std::string text;
    std::string group_name;
    bool training;
}Config;

Config get_config(int argc, char** argv);
