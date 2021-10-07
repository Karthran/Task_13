#pragma once
#include <iostream>

#define VALUE_NOT_FOUND -1

#include "BadException.h"

template <typename T>
class Array
{
public:
    Array() = default;
    Array(int length);
    Array(const Array& other);
    ~Array();
    auto operator=(const Array& other) -> Array&;

    auto erase() -> void;
    auto operator[](int index) const -> T&;
    auto reallocate(int newLength) -> void;
    auto resize(int newLength) -> void;
    auto insertBefore(T value, int index) -> void;
    auto remove(int index) -> void;
    auto insertAtBeginning(T value) -> void;
    auto insertAtEnd(T value) -> void;
    auto findValue(T value) const -> int;
    auto getArrayLength() const -> int;

private:
    int _length{0};
    std::shared_ptr<T[]> _data;
};

template <typename T>
Array<T>::Array(int length) : _length(length), _data(new T[_length]{})
{
    if (_length <= 0) throw bad_length();
}

template <typename T>
Array<T>::Array(const Array<T>& other) : _length(other._length), _data(new T[_length]{})
{
    if (_length <= 0) throw bad_length();

    for (int i = 0; i < _length; ++i)
    {
        _data[i] = other._data[i];
    }
}

template <typename T>
auto Array<T>::operator=(const Array<T>& other) -> Array<T>&
{
    if (this == &other) return *this;

    _length = other._length;
    if (_length <= 0) throw bad_length();

    std::shared_ptr<T> ptr(new T[_length]);

    _data = ptr;

    for (int i = 0; i < _length; ++i)
    {
        _data[i] = other._data[i];
    }
    return *this;
}

template <typename T>
Array<T>::~Array()
{
}

template <typename T>
auto Array<T>::erase() -> void
{
    _data = nullptr;
    _length = 0;
}

template <typename T>
auto Array<T>::operator[](int index) const -> T&
{
    if (index < 0 || index >= _length) throw bad_range();

    return _data[index];
}

template <typename T>
auto Array<T>::reallocate(int newLength) -> void
{
    if (newLength <= 0) throw bad_length();

    erase();
    _length = newLength;
    std::shared_ptr<T[]> ptr(new T[_length] {});
    _data = ptr;
}

template <typename T>
auto Array<T>::resize(int newLength) -> void
{
    if (newLength <= 0) throw bad_length();
    if (_length == newLength) return;

    int totalLength = (_length > newLength) ? newLength : _length;

    std::shared_ptr<T[]> newPtr { new T[newLength] {} };

    for (int i{0}; i < totalLength; ++i)
    {
        newPtr[i] = _data[i];
    }
    _data = newPtr;
    _length = newLength;
}

template <typename T>
auto Array<T>::insertBefore(T value, int index) -> void
{
    if (index < 0 || index > _length) throw bad_range();

    std::shared_ptr<T[]> newPtr { new T[ _length + 1 ] };

    for (int i{0}; i < index; ++i)
        newPtr[i] = _data[i];

    newPtr[index] = value;

    for (int i{index}; i < _length; ++i)
        newPtr[i + 1] = _data[i];

    _data = newPtr;
    ++_length;
}

template <typename T>
auto Array<T>::remove(int index) -> void
{
    if (index < 0 || index >= _length) throw bad_range();

    if (_length == 1)
    {
        erase();
        return;
    }

    std::shared_ptr<T[]> newPtr { new T[ _length - 1 ] };

    for (int i{0}; i < index; ++i)
        newPtr[i] = _data[i];

    for (int i{index}; i < _length - 1; ++i)
        newPtr[i] = _data[i + 1];

    _data = newPtr;
    --_length;
}
template <typename T>
auto Array<T>::insertAtBeginning(T value) -> void
{
    insertBefore(value, 0);
}

template <typename T>
auto Array<T>::insertAtEnd(T value) -> void
{
    insertBefore(value, _length);
}

template <typename T>
auto Array<T>::findValue(T value) const -> int
{
    for (int i{0}; i < _length; ++i)
    {
        if (_data[i] != value) continue;
        return i;
    }
    return VALUE_NOT_FOUND;
}

template <typename T>
auto Array<T>::getArrayLength() const -> int
{
    return _length;
}
