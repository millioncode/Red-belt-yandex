#include "test_runner.h"

#include <numeric>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

// Реализуйте шаблон класса Paginator
template <typename Iterator>
class Page {
    public:
        Page(Iterator first, Iterator last):_first(first), _last(last) {

        }
        size_t size() const {
            return _last - _first;
        }
        Iterator begin() {
            return _first;
        }
        Iterator begin() const {
            return _first;
        }
        Iterator end() {
            return _last;
        }
        Iterator end() const {
            return _last;
        }
        typedef Iterator iterator;
        typedef Iterator const_iterator;
    private:
        Iterator _first, _last;
};
template <typename Iterator>
Page<Iterator> MakePage(Iterator s, Iterator f) {
    return {s,f};
}
template <typename Iterator>
class Paginator {
    public:
        Paginator(Iterator first, Iterator last, size_t page):
            _first(first), _last(last), _page(page) {

            for( Iterator it = _first; _first!=_last && it<_last; it+=_page) {
                if (it+_page <= _last) _base.push_back(Page<Iterator>(it, it+_page) );
                else _base.push_back(Page<Iterator>(it, _last) );
            }
        }
        typename vector<Page<Iterator>>::iterator begin() {return _base.begin();}
        typename vector<Page<Iterator>>::iterator  end() {return _base.end();}
        typename vector<Page<Iterator>>::const_iterator begin() const{return _base.begin();}
        typename vector<Page<Iterator>>::const_iterator  end() const{return _base.end();}

        size_t size() const {
            return _base.size();
        }
    private:
        Iterator _first, _last;
        size_t _page;
        vector <Page<Iterator>> _base;
};

template <typename Container>
Paginator<typename Container::iterator>
    Paginate(Container& c, size_t page_size) {
    // Реализуйте этот шаблон функции
    return {c.begin(), c.end(), page_size};
}
template <typename Container>
Paginator<typename Container::const_iterator>
    Paginate(const Container& c, size_t page_size) {
         return {c.begin(), c.end(), page_size};
}
void TestPageCounts() {
    vector<int> v(15);

    ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
    ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
    ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
    ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
    ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
    ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
    ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
    // мой, как будет вести при 0
    vector <int> vv;
    ASSERT_EQUAL(Paginate(vv, 1).size(), 0);
}

void TestLooping() {
    vector<int> v(15);
    iota(begin(v), end(v), 1);

    Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
    ostringstream os;
    for (const auto& page : paginate_v) {
        for (int x : page) {
            os << x << ' ';
        }
        os << '\n';
    }

    ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}

void TestModification() {
    vector<string> vs = {"one", "two", "three", "four", "five"};
    for (auto page : Paginate(vs, 2)) {
        for (auto& word : page) {
            word[0] = toupper(word[0]);
        }
    }

    const vector<string> expected = {"One", "Two", "Three", "Four", "Five"};
    ASSERT_EQUAL(vs, expected);
}

void TestPageSizes() {
    string letters(26, ' ');

    Paginator letters_pagination(letters.begin(), letters.end(), 11);
    vector<size_t> page_sizes;
    for (const auto& page : letters_pagination) {
        page_sizes.push_back(page.size());
    }

    const vector<size_t> expected = {11, 11, 4};
    ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer() {
    const string letters = "abcdefghijklmnopqrstuvwxyz";

    vector<string> pages;
    for (const auto& page : Paginate(letters, 10)) {
        pages.push_back(string(page.begin(), page.end()));
    }

    const vector<string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
    ASSERT_EQUAL(pages, expected);
}

void TestPagePagination() {
    vector<int> v(22);
    iota(begin(v), end(v), 1);

    vector<vector<int>> lines;
    for (const auto& split_by_9 : Paginate(v, 9)) {
        for (const auto& split_by_4 : Paginate(split_by_9, 4)) {
            lines.push_back({});
            for (int item : split_by_4) {
                lines.back().push_back(item);
            }
        }
    }

    const vector<vector<int>> expected = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9},
        {10, 11, 12, 13},
        {14, 15, 16, 17},
        {18},
        {19, 20, 21, 22}
    };
    ASSERT_EQUAL(lines, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestPageCounts);
    RUN_TEST(tr, TestLooping);
    RUN_TEST(tr, TestModification);
    RUN_TEST(tr, TestPageSizes);
    RUN_TEST(tr, TestConstContainer);
    RUN_TEST(tr, TestPagePagination);
}

