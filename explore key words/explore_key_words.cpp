#include "test_runner.h"
#include "profile.h"

#include <map>
#include <set>
#include <string>

#include <algorithm>
#include <string_view>
#include <iterator>
#include <future>
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
    string::const_iterator it;
    while ( (it = find(first, last, ' ')) <= last ) {
        string word(first, it);
        if (*key_words.lower_bound(word)==word) {
            result.word_frequences[word]++;
        }
        if (it!=last) first = it+1;
        else break;
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
    return ExploreKeyWordsSingleThread(key_words, input);

}
void TestOne() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};
    string ss {"this new yangle service really rocks"};
    const map<string, int> expected = {
            {"yangle", 1},
            {"rocks", 1},
        };
    const auto stats = ExploreLine(key_words, ss);
    ASSERT_EQUAL(stats.word_frequences, expected);
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
    RUN_TEST(tr, TestOne);
    RUN_TEST(tr, TestBasic);
}
