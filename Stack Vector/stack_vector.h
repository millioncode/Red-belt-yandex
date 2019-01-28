// почему-то грейдер ругается на прагму
#pragma once
#include <stdexcept>
#include <array>
#include <iterator>
using namespace std;

template <typename T, size_t N>
class StackVector {
    public:
        explicit StackVector(size_t a_size = 0): capa_(N), size_(a_size),
        first_(massive_.begin()) {
            if (a_size > N ) throw invalid_argument("Constructor");
        }

        T& operator[](size_t index) {
            return massive_[index];
        }
        const T& operator[](size_t index) const {
            return massive_[index];
        }

        typename array<T,N>::iterator begin() {return first_;}
        auto end()
        {
            return last_;
        }
        typename array<T,N>::iterator begin() const{return first_;}
        typename array<T,N>::iterator end() const{
            return last_;
        }

        size_t Size() const {return size_;}
        size_t Capacity() const {return capa_;}

        void PushBack(const T& value) {
            if (capa_ == size_) throw overflow_error("push");
            else {
                massive_[size_] = value;
                ++size_;
            }
        }
        T PopBack() {
            if (size_ == 0) throw underflow_error("pop");
            else {
                --size_;
                return massive_[size_];
            }
        }

    private:
        array <T, N> massive_;

        size_t capa_;
        size_t size_;
        // много крови выпил тип итератора аrray<T,N>
        typename array<T,N>::iterator first_;
        typename array<T,N>::iterator last_ = first_ + size_;
};
