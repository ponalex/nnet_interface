#include "normalizer.h"
#include <cctype>
#include <clocale>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <locale>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

Normalizer::Normalizer(std::locale c_loc, size_t b_size):
    loc(c_loc),block_size(b_size){};

std::wostream& operator<<(std::wostream& wostrm, Normalizer& normalizer){
    wostrm << normalizer.buffer;
    return wostrm;
}

std::wstring Normalizer::get_substring(size_t first_char, size_t char_number){
    std::wstring line;
    line = buffer.substr(first_char, char_number);
    return  line;
}

size_t Normalizer::read_text(std::string& filename, size_t position){
    wchar_t symbol;
    size_t counter = 0;
    std::wifstream wfile(filename);
    wfile.imbue(loc);
    wfile.seekg(position);
    while(counter < block_size){
        wfile.get(symbol);
        if(wfile.eof() || wfile.bad()){
            break;
        }
        ++counter;
        if (std::isspace(symbol, loc)){
            symbol = L' ';
        }
        if (std::isupper(symbol, loc)){
            symbol = std::tolower(symbol, loc);
        }
        buffer = buffer + symbol;
    }
    wfile.close();
    if (counter < block_size){
        for (size_t i = counter ; i < block_size ; ++i){
            buffer = buffer + L' ';
        }
    }
    return counter; 
};
        
size_t Normalizer::get_block_size(){
    return block_size;
}
    
template<typename T>
size_t Normalizer::calc_vector(TokenStream<T>& tokens, 
                            std::vector<T>& embedded_vec,
                            size_t position, uint min_length){
    size_t result = 0;
    std::wstring substring ;
    uint n_char = min_length;
    if(position >= block_size) return 0;
    do{
        substring = buffer.substr(position, n_char);
        embedded_vec = tokens.get_vector(substring);
        if(embedded_vec.size() == 0) --n_char;
        else{
            std::vector<T> vec = embedded_vec;
        }
    }while(embedded_vec.size() == 0 && n_char > 0);
    result = position + n_char;
    return result;
}

//  **********************************************************
template<typename T>
TokenStream<T>::TokenStream(std::locale& locale):delimeter(L' '),loc(locale){};

template<typename T>
TokenStream<T>::TokenStream(std::locale& locale,wchar_t symbol):delimeter(symbol),loc(locale){};

template <typename S>
std::wistream& operator>>(std::wistream& strm, TokenStream<S>& tstream){
    wchar_t symbol;
    S number;
    std::vector<S> vec;
    std::wstring wline;
    std::wstring pattern;
    size_t position;
    std::wstringstream wstrm;
    wstrm.imbue(tstream.loc);
    while(std::getline(strm, wline)){
        position = wline.find(tstream.delimeter);
        pattern = wline.substr(0, position);
        wline = wline.substr(position+1);
        wstrm.clear();
        wstrm << wline;
        do{
            wstrm >> number;
            if(wstrm.fail()){
                wstrm.unget();
                vec.clear();
                vec.push_back(-1);
                break;
            }
            vec.push_back(number);
        }while(!wstrm.eof());
        tstream.tokens[pattern] = vec;
        vec.clear();
    }
    return strm;
}

template<typename S>
std::vector<S> TokenStream<S>::get_vector(std::wstring& line){
    return tokens[line];
}

template class TokenStream<int>;
template std::wistream& operator>>(std::wistream& strm, TokenStream<int>& tstream);
template size_t Normalizer::calc_vector(TokenStream<float>& tokens, 
                            std::vector<float>& embedded_vec,
                            size_t position, uint min_length);
template size_t Normalizer::calc_vector(TokenStream<double>& tokens, 
                            std::vector<double>& embedded_vec,
                            size_t position, uint min_length);
template size_t Normalizer::calc_vector(TokenStream<int>& tokens, 
                            std::vector<int>& embedded_vec,
                            size_t position, uint min_length);
