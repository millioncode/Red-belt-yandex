#include "test_runner.h"
#include <string>
#include <vector>
#include <string_view>
#include <map>
#include <queue>
using namespace std;

class Translator {
    public:
        //source - target
        void Add(string_view source, string_view target) {
            all_words.emplace(source, target);
            source_target[all_words.back().first] = all_words.back().second;
            target_source[all_words.back().second] = all_words.back().first;
        }

        string_view TranslateForward(string_view source) const {
            auto it = source_target.lower_bound(source);
            if ( (*it).first != source ) {
                return string("");
            }
            else {
                return (*it).second;
            }
        }
        string_view TranslateBackward(string_view target) const {
            auto it = target_source.lower_bound(target);
            if ( (*it).first != target ) {
                return string("");
            }
            else {
                return (*it).second;
            }
        }

    private:
        map <string_view, string_view> source_target;
        map <string_view, string_view> target_source;
        queue <pair<string, string>> all_words;
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
