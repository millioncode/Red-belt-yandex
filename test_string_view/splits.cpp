#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <string_view>
using namespace std;
vector <string> SplitString (const string& words) {
    vector <string> result;
    auto words_begin = begin(words);
    const auto words_end = end(words);
    while (true) {
        auto it = find(words_begin, words_end, ' ');
        result.push_back(string(words_begin, it) );
        if (it == words_end) {
            break;
        }
        else {
            words_begin = it + 1;
        }
    }
    return result;
}
vector <string_view> SplitStringView (const string& words) {
    vector <string_view> result;
    string_view _words = words;

    size_t pos = 0;
    // string_view не работает с итерраторами, т.к. работает с подряд идущими символами
    // конец будет npos
    size_t pos_end = _words.npos;
    while (1) {
        size_t space = _words.find(' ', pos);
        result.push_back(space==pos_end ?
                           _words.substr(pos) :
                             _words.substr(pos, space - pos));
        if (space == pos_end) {
            break;
        }
        else {
            pos = space + 1;
        }
    }
    return result;
}
string Prepare(const size_t& number) {
    string words(number, 'a');
    for(size_t i=0; i<number; i+=100) {
        words[i] = ' ';
    }
    return words;
}
