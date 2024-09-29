#include <cstddef>
#include <istream>
#include <locale>
#include <ostream>
#include <random>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

template<typename T> class TokenStream{
    private:
        std::map<std::wstring, std::vector<T>> tokens;
        std::locale loc;
        wchar_t delimeter;
    public:
        TokenStream(std::locale& local);
        TokenStream(std::locale& local, wchar_t symbol);
        template<typename S>
        friend std::wistream& operator>>(std::wistream& strm, TokenStream<S>& tokens);
        std::vector<T> get_vector(std::wstring& line);
};

class Normalizer{
    private:
        std::locale loc;
        std::wstring buffer;
        size_t block_size;
    public:
        Normalizer(std::locale loc, size_t block_size);
        size_t read_text(std::string& filename, size_t position);   //  Return the number of read words
        friend std::wostream& operator<<(std::wostream& wostrm, Normalizer& normalizer);
        std::wstring get_substring(size_t first_symbol, size_t char_number);
        size_t get_block_size();
        template<typename T>
        size_t calc_vector(TokenStream<T>& tokens, 
                            std::vector<T>& embedded_vec,
                            size_t position, uint min_length=2);
};
//  #link
//  /*  */
//  ~   ~   -   ignore
//  @<Key word>
//  &   &   -    ignore
//  [   ]   -   Keep ready
//  <   >   -   Keep ready
//
// #include "normalizer.tpp"
// template std::istream& operator>>(std::istream& istrm, Tocken<int>& tocken);
// template std::istream& operator>>(std::istream& istrm, Tocken<float>& tocken);
// template std::istream& operator>>(std::istream& istrm, Tocken<double>& tocken);
