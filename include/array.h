#pragma once

#include <memory>
#include <utility> 
#include <concepts>
#include <cassert>


template <class T>
concept Arrayable = std::is_default_constructible_v<T>;

template <Arrayable T>
class Array
{
public:
    Array() : _size(0), _capacity(1), _array(std::make_unique<T[]>(_capacity)) {}

    void push_back(const T& item) {
        if (_size == _capacity) {
            resize(); 
        }
        _array[_size++] = item;
    }

    void push_back(T&& item) {
        if (_size == _capacity) {
            resize(); 
        }
        _array[_size++] = std::move(item);
    }

    void remove(size_t index) {
        if (index >= _size) return;

        for (size_t i = index; i < _size - 1; ++i) {
            _array[i] = std::move(_array[i + 1]); 
        }
        --_size;
    }

    T& operator[](size_t index) {
        assert(index<_size);
        return _array[index];
    }


    const T& operator[](size_t index) const {
        assert(index < _size);
        return _array[index];
    }


    size_t size() const{
        return _size;
    }

    ~Array() noexcept
    {
        // std::cout << "destructor:" << _array.use_count() << std::endl;
    }

    

private:
    void resize() {
        size_t new_capacity = _capacity * 2; 
        auto new_array = std::make_unique<T[]>(new_capacity);

        for (size_t i = 0; i < _size; ++i) {
            new_array[i] = std::move(_array[i]); 
        }

        _array = std::move(new_array);
        _capacity = new_capacity;
    }

private:
    size_t _size;    
    size_t _capacity; 
    std::unique_ptr<T[]> _array; 
};