#include "src/normalizer.h"
#include <cctype>
#include <clocale>
#include <cstddef>
#include <cwctype>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
// use g++ -std=c++11
#define PATTERN_FILE "texts/pattern.txt"
#define LETTER_FILE "letter.txt"

void load_tokens(std::string& filename, TokenStream<int>& tokens){
    std::wifstream wfile(filename);
    wfile.imbue(std::locale("ru_RU.utf8"));
    wfile >> tokens;
    wfile.close();
}



int main(int argc, char* argv[]){

    std::setlocale(LC_ALL, "C.utf8");
    std::locale c_locale("ru_RU.utf8");
    std::string pattername = PATTERN_FILE;
    std::string textname = "texts/text.txt";
    Normalizer textsource(c_locale, 5);
    TokenStream<int> tokens(c_locale, L'&');
    load_tokens(pattername, tokens);
    textsource.read_text(textname, 0);

    std::wstring temp = L"а";
    std::vector<int> vec;
    size_t position = 0;
    while(position < textsource.get_block_size()) {  
        position = textsource.calc_vector(tokens, vec, position, 2);
        for(auto l : vec){
            std::wcout << l << " ";
        }
        vec.clear();
    }
    std::wcout << textsource << "\n";
    return 0;
}
