#include <iostream>
#include <vector>
#include <exception>
#include "test_runner.h"
using namespace std;
template <typename T>
class Deque {
    public:
        Deque(size_t num=0) {
            if (num!=0) Resize(num);
        }
        void Resize(size_t num) {
            HEAD.resize(0);
            JOPA.resize(num);
        }
        bool Empty() const {
            return (HEAD.empty() && JOPA.empty());
        }
        size_t Size() const {
            return HEAD.size()+JOPA.size();
        }
        T& operator[](size_t index) {
            size_t value = HEAD.size();
            return (index<value) ? HEAD[value-1-index]: JOPA[index-value];
        }
        const T& operator[](size_t index) const {
            size_t value = HEAD.size();
            return (index<value) ? HEAD[value-1-index]: JOPA[index-value];
        }
        T& At(const size_t index) {
            // проверку на размерность можно вынести как отдельный метод - чтобы
            // не было дублирования кода
            if (index>= Size() ) throw out_of_range("out of range");
            size_t value = HEAD.size();
            return (index<value) ? HEAD[value-1-index]: JOPA[index-value];
        }
        const T& At(const size_t index) const {
            if (index>= Size() ) throw runtime_error("out of range");
            size_t value = HEAD.size();
            return (index<value) ? HEAD[value-1-index]: JOPA[index-value];
        }
        T& Front() {
            return (HEAD.empty()) ? JOPA.front(): HEAD.back();
        }
        const T& Front() const {
            return (HEAD.empty()) ? JOPA.front(): HEAD.back();
        }
        T& Back() {
            return (JOPA.empty()) ? HEAD.front(): JOPA.back();
        }
        const T& Back() const {
            return (JOPA.empty()) ? HEAD.front(): JOPA.back();
        }
        void PushFront(T x) {
            HEAD.push_back(x);
        }
        void PushBack(T x) {
            JOPA.push_back(x);
        }
    private:
        vector <T> HEAD;
        vector <T> JOPA;
};
void TestTable() {
    try {
        Deque <int> t(3);
        ASSERT_EQUAL(t.Empty(), false);
        ASSERT_EQUAL(t.Size(), 3);
        t[0] = 1;
        ASSERT_EQUAL(t[0], 1);
        t[2] = 3;
        ASSERT_EQUAL(t[2], 3);
        t.At(2) = 41;
        ASSERT_EQUAL(t.At(2), 41);
        ASSERT_EQUAL(t.Front(), 1u);
        ASSERT_EQUAL(t.Back(), 41);
        t.PushFront(-2);
        ASSERT_EQUAL(t.Front(), -2);
        ASSERT_EQUAL(t.Size(), 4);
        t.PushBack(42);
        ASSERT_EQUAL(t.Back(), 42);
        ASSERT_EQUAL(t.Size(), 5);
        t.PushFront(-1);
        ASSERT_EQUAL(t.Front(), -1);
    } catch (exception& ex) {
        cout << ex.what() << endl;
    }
}
int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
