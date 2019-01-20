#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <deque>

using namespace std;

template <class T>
class ObjectPool {
    public:
        //Методы Allocate и TryAllocate должны возвращать объекты в порядке FIFO, т.е. множество освобождённых объектов должно представлять собой очередь: методы [Try]Allocate должны извлекать объекты из её начала, а метод Deallocate должен помещать освобождаемый объект в её конец.
        T* Allocate() {
            if (!free_obj.empty()) {
                /*если есть хотя бы один освобождённый объект, то его надо перенести в множество выделенных и вернуть указатель на него в качестве результата функции */
                T* ptr1 = free_obj.front();
                full_obj.insert(ptr1);
                free_obj.pop_front();
                return ptr1;
            }
            else {
                /*если же освобождённых объектов нет, то создаётся новый объект, помещается в множество выделенных, и указатель на него возвращается в качестве результата функции*/
                T* ptr2 = new T;
                full_obj.insert(ptr2);
                return ptr2;
            }
        }

        T* TryAllocate(){
            if (!free_obj.empty()) {
                /*Метод TryAllocate работает аналогично, однако если освобождённых объектов нет, он должен просто возвращать nullptr.*/
                T* ptr1 = free_obj.front();
                full_obj.insert(ptr1);
                free_obj.pop_front();
                return ptr1;
            } else return nullptr;
        }
        void Deallocate(T* object) {
            /*Метод Deallocate переносит объект из множества выделенных в множество освобождённых; если переданный объект не содержится в множестве выделенных, метод Deallocate должен бросать исключение invalid_argument.*/
            auto value = full_obj.find(object);
            if (value==full_obj.end()) {
                throw invalid_argument("");
            }
            free_obj.push_back(object);
            full_obj.erase(value);
        }

        ~ObjectPool() {
            for(auto& elem : full_obj) {
                delete elem;
            }
            for(auto& elem : free_obj) {
                delete elem;
            }
        };

    private:
        // 2 набора объектов выделенные и освобожденные-очередь
        set <T*> full_obj;
        deque <T*> free_obj;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
