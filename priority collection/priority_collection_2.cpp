#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;
static size_t ID {0};
template <typename T>
class PriorityCollection {
    public:
        using Id = size_t/* тип, используемый для идентификаторов */;

        // Добавить объект с нулевым приоритетом
        // с помощью перемещения и вернуть его идентификатор
        Id Add(T object) {
            Id id = ID++;
            data_.push_back({0, id, move(object)});
            return id;
        }

        // Добавить все элементы диапазона [range_begin, range_end)
        // с помощью перемещения, записав выданные им идентификаторы
        // в диапазон [ids_begin, ...)
        template <typename ObjInputIt, typename IdOutputIt>
        void Add(ObjInputIt range_begin, ObjInputIt range_end,
                 IdOutputIt ids_begin);

        // Определить, принадлежит ли идентификатор какому-либо
        // хранящемуся в контейнере объекту
        bool IsValid(Id id) const;

        // Получить объект по идентификатору
        const T& Get(Id id) const;

        // Увеличить приоритет объекта на 1
        void Promote(Id id) {
            for(auto& i : data_) {
                if (i.id == id) {
                    i.priority++;
                }
            }
        }

        // Получить объект с максимальным приоритетом и его приоритет
        pair<const T&, int> GetMax() const {
            Item* max = data_.front();
            for(const auto& value:data_) {
                if (value.priority >= (*max).priority) {
                    max = &value;
                }
            }
            return { (*max).data, (*max).priority };
        }

        // Аналогично GetMax, но удаляет элемент из контейнера
        pair<T, int> PopMax() {
            auto max = data_.begin();
            for(auto it = next(data_.begin()); it!=data_.end(); it++) {
                if ( (*it).priority >= (*max).priority ) {
                    max = it;
                }
            }
            auto result = make_pair(move(max->data), max->priority);
            data_.erase(max);
            return move(result);
        }

    private:
        // Приватные поля и методы
        struct Item {
                size_t priority = 0;
                size_t id = 0;
                T data;
        };
        vector <Item> data_;
};


class StringNonCopyable : public string {
    public:
        using string::string;  // Позволяет использовать конструкторы строки
        StringNonCopyable(const StringNonCopyable&) = delete;
        StringNonCopyable(StringNonCopyable&&) = default;
        StringNonCopyable& operator=(const StringNonCopyable&) = delete;
        StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
