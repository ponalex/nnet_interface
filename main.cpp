#include "src/normalizer.h"
#include <cctype>
#include <clocale>
#include <cwctype>
#include "src/options.h"
#include <locale>
#include <iostream>
// use g++ -std=c++11
#define PATTERN_FILE "texts/pattern.txt"
#define LETTER_FILE "letter.txt"



int main(int argc, char* argv[]){

    std::setlocale(LC_ALL, "C.utf8");
    std::locale c_locale("ru_RU.utf8");
    Config configuration = get_config(argc, argv); 
    std::cout << configuration.text << "\n";
    std::cout << configuration.group_name << "\n";
    return 0;
}
