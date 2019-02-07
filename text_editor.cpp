#include <string>
#include <list>
#include <string_view>
#include "test_runner.h"
using namespace std;

class Editor {
    public:
        // Реализуйте конструктор по умолчанию и объявленные методы
        Editor(): POS_it(TEXT.begin()), POS_(0) {}
        void Left() {
            if (POS_it != TEXT.begin()) {
                --POS_it;
                POS_--;
            }
        }
        void Right() {
            if (POS_ < TEXT.size()) {
                ++POS_it;
                POS_++;
            }
        }
        void Insert(char token) {
            TEXT.insert( POS_it, token);
            POS_++;
        }
        void Cut(size_t tokens = 1) {
            BUF.clear();
            if (tokens!=0) {
                auto first = POS_it;
                auto value = POS(tokens);
                list <char>::iterator last;
                if (POS_+tokens > TEXT.size()) {
                    last = TEXT.end();
                }
                else {
                    last = value;
                }
                BUF = {first, last};
                POS_it = last;
                TEXT.erase(first, last);
            }
        }
        void Copy(size_t tokens = 1) {
            BUF.clear();
            auto first = POS_it;
            auto last = POS(tokens);
            BUF = {first, last};
        }
        void Paste() {
            if (!BUF.empty()) {
                TEXT.insert(POS_it, BUF.begin(), BUF.end());
                auto value = BUF.size();
                POS_ += value;
            }
        }
        string GetText() const {
            return {TEXT.begin(), TEXT.end()};
        }
        list <char>::iterator POS(size_t value = 0) {
            auto it = POS_it;
            for (size_t i=0; i<value; i++) {
                ++it;
            }
            return it;
        }
    public:
        list <char> TEXT;
        string BUF;
        list <char>::iterator POS_it;
        size_t POS_;
};

void TypeText(Editor& editor, const string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        ASSERT_EQUAL(editor.GetText(), "hello, world");
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }

        // world
        editor.Cut(first_part_len);
        ASSERT_EQUAL(editor.GetText(), "world");
        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        ASSERT_EQUAL(editor.GetText(), "world, ");
        // world,
        editor.Paste();
        // world, hello,_
        ASSERT_EQUAL(editor.GetText(), "world, hello, ");

        editor.Left();
        editor.Left();

        editor.Cut(3); // почему 3 ????

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}
void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}
int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}
