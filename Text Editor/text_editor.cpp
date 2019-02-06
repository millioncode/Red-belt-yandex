#include <string>
#include <deque>
#include "test_runner.h"
using namespace std;

class Editor {
    public:
        // Реализуйте конструктор по умолчанию и объявленные методы
        Editor(): POS_(1) {
            TEXT.push_back('|');
        }
        void Left() {
            if (POS_>0) {
                POS_--;
                swap(TEXT[POS_], TEXT[POS_+1]);
            }
        }
        void Right() {
            if (POS_ < 1'000'000) {
                POS_++;
                swap(TEXT[POS_], TEXT[POS_-1]);
            }
        }
        void Insert(char token) {
            auto it = TEXT.begin()+POS_;
            TEXT.insert(it, token);
            POS_++;
        }
        void Cut(size_t tokens = 1) {
            auto first = TEXT.begin()+POS_;
            auto last = first + tokens;
            BUF = {first, last};
            TEXT.erase(first, last);
            BUF.clear();

        }
        void Copy(size_t tokens = 1) {
            auto first = TEXT.begin()+POS_;
            auto last = first + tokens;
            BUF = {first, last};
        }
        void Paste() {
            if (!BUF.empty()) {
                TEXT.insert(TEXT.begin()+POS_, BUF.begin(), BUF.end());
                BUF.clear();
            }
        }
        string GetText() const {
            string result(TEXT.begin(), TEXT.end());
            return result;
        }
    public:
        //container
        deque <char> TEXT;
        // string_view ?
        string BUF;
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
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

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
/*
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
*/
int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    /*RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);*/
    return 0;
}
