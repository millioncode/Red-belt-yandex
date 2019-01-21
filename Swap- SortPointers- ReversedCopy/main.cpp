#include "test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;

template <typename T>
void Swap(T* first, T* second) {
    swap(*first, *second);
}

template <typename T>
void SortPointers(vector<T*>& pointers){
    sort(pointers.begin(), pointers.end(), [](T* left, T* right){
        return *left<*right;
    } );
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination) {
    auto first = source;
    auto last = source+count;
    T* d_first = new T [count];
    reverse_copy(first, last, d_first);
    copy(d_first, d_first+count, destination);
    delete [] d_first;
}

void TestSwap() {
    int a = 1;
    int b = 2;
    Swap(&a, &b);
    ASSERT_EQUAL(a, 2);
    ASSERT_EQUAL(b, 1);

    string h = "world";
    string w = "hello";
    Swap(&h, &w);
    ASSERT_EQUAL(h, "hello");
    ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
    int one = 1;
    int two = 2;
    int three = 3;

    vector<int*> pointers;
    pointers.push_back(&two);
    pointers.push_back(&three);
    pointers.push_back(&one);

    SortPointers(pointers);

    ASSERT_EQUAL(pointers.size(), 3u);
    ASSERT_EQUAL(*pointers[0], 1);
    ASSERT_EQUAL(*pointers[1], 2);
    ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
    const size_t count = 7;

    int* source = new int[count];
    int* dest = new int[count];

    for (size_t i = 0; i < count; ++i) {
        source[i] = i + 1;
    }
    ReversedCopy(source, count, dest);
    const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
    ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

    // Области памяти могут перекрываться
    ReversedCopy(source, count - 1, source + 1);
    const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
    ASSERT_EQUAL(vector<int>(source, source + count), expected2);

    delete[] dest;
    delete[] source;
}
/*template <typename T>
void ReversedCopy(T *source, size_t count, T *destination) {
  for (int i = 0; i <= count - 1; i++) {
    T *s = source + i;
    T *d = destination + (count - 1 - i);
    if (s == d) {
      // сошлись
      break;
    } else if ((s < destination) || (s > destination + count - 1)) {
      // если исходный указатель не лежит в диапазоне копирования destination -
      // копируем
      *d = *s;
    } else if ((s >= destination) && (s <= destination + count - 1)) {
      // если лежит, делаем swap
      swap(*d, *s);
    }
  }
}*/
int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSwap);
    RUN_TEST(tr, TestSortPointers);
    RUN_TEST(tr, TestReverseCopy);
    return 0;
}
