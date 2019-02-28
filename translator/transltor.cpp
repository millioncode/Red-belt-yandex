#include "test_runner.h"
#include <string>
#include <vector>
#include <string_view>
#include <map>
using namespace std;

class Translator {
    public:
        //source - target
        void Add(string_view source, string_view target) {
            source_target[string(source)] = target;
            target_source[string(target)] = source;
        }

        string_view TranslateForward(string_view source) const {
            string word (source);
            auto it = source_target.lower_bound(word);
            if ( (*it).first != word ) {
                return string("");
            }
            else {
                return (*it).second;
            }

            //return source_target.at(string(source));
        }
        string_view TranslateBackward(string_view target) const {
            string word (target);
            auto it = target_source.lower_bound(word);
            if ( (*it).first != word ) {
                return string("");
            }
            else {
                return (*it).second;
            }
        }

    private:
        map <string, string> source_target;
        map <string, string> target_source;
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
