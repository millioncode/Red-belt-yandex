#include "test_runner.h"
#include "profile.h"

#include <map>
#include <set>
#include <string>

#include <algorithm>
#include <string_view>
#include <iterator>
#include <typeinfo>
using namespace std;

struct Stats {
        map<string, int> word_frequences;

        void operator += (const Stats& other) {
            for (const auto& word : other.word_frequences) {
                word_frequences[word.first] += word.second ;
            }
        }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    string::const_iterator first = line.begin();
    string::const_iterator last = line.end();
    Stats result;
    while ( (string::const_iterator it = find(first, last, ' ')) != last ) {
        string word(first, it);
        if (*key_words.lower_bound(word)==word) {
            result.word_frequences[word]++;
        }
        first = it;
    }
    return result;
}

Stats ExploreKeyWordsSingleThread(
        const set<string>& key_words, istream& input
        ) {
    Stats result;
    for (string line; getline(input, line); ) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    // Реализуйте эту функцию
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    //RUN_TEST(tr, TestBasic);

    const string s {"abcdef"};
    string::const_iterator b = s.begin();
    auto e = s.end();
    string ss (b,e);
    cout << ss << endl;

}
