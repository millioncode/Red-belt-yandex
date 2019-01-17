#include "test_runner.h"
#include <tuple>
using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Table {
    public:
        Table(size_t row, size_t columns): _row(row), _columns(columns) {
            Resize(row, columns);
        }
        void Resize(size_t new_row, size_t new_col) {
            table.resize(new_row);
            for(size_t i=0; i<new_row; i++ ) {
                table[i].resize(new_col);
            }
            _row=new_row;
            _columns=new_col;
        }
        pair <size_t, size_t> Size() const {
            return make_pair(_row, _columns);
        }
        vector<T>& operator [](const int index) {
            return table[index];
        }
        const vector<T>& operator [](const int index) const {
            return table[index];
        }
    private:
        size_t _row;
        size_t _columns;
        vector <vector<T> > table;
};
void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
