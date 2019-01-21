#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
    public:
        SimpleVector() {
            data_ = nullptr;
            end_ = data_;
            size_ = 0;
            capa_ = 0;
        }
        explicit SimpleVector(size_t size) {
            size_ = size;
            capa_ = 2*size_;
            data_ = new T [capa_];
            end_ = data_+size;
        }
        ~SimpleVector() {
            if (data_ != nullptr) {
                delete [] data_;
            }
            capa_=0;
            size_=0;
        }

        T& operator[](size_t index) {
            return *(data_ + index);
        }

        T* begin() {
            return data_;
        }
        T* end() {
            return end_;
        }
        const T* begin() const {
            return data_;
        }
        const T* end() const {
            return end_;
        }

        size_t Size() const {
            return size_;
        }
        size_t Capacity() const {
            return capa_;
        }
        void PushBack(const T& value);

    private:
        T* data_;
        T* end_;
        size_t size_;
        size_t capa_;
        // Добавьте поля для хранения данных вектора
};
template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
    if (Size() >= Capacity()) {
        if(capa_!=0) {
            capa_ *= 2;
        } else capa_=2;

        T* ptr = new T[capa_];
        //copy(data_, end_, ptr);
        for(size_t i=0; i<size_; i++) {
            ptr[i]=data_[i];
        }
        delete [] data_;
        data_ = ptr;
        data_[size_++] = value;
        end_ = data_ + size_;
    }
    else {
        data_[size_++] = value;
        end_ = data_ + size_;
    }
}
