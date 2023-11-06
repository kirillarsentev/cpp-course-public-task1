#pragma once
#include "template_iterator.hpp"

template <class T>
class Vector
{
public:
static const size_t reserve_miltiply_ = 2;
static const size_t empty_vector_size_ = 8;
public:
using iterator = Iterator<T>;
using value_type = T;
using pointer = T*;
using reference = T&;
using size_type = size_t;

Vector()
{
size_ = 0;
capacity_ = empty_vector_size_;
data_ = new T[empty_vector_size_];
}

~Vector()
{
delete[] data_;
}

reference operator[] (size_type n) {
if (n < 0 or (n >= (int)size_))
throw std::out_of_range("index is outside");
return data_[n];
}

const reference operator[] (size_type n) const {
if (n < 0 or (n >= (int)size_))
throw std::out_of_range("index is outside");
return data_[n];
}

void push_back(const T & value) {
if (size_ >= capacity_)
{
reserve(capacity_ * reserve_miltiply_);
}
data_[size_++] = value;
}

void push_back(T && value) {
if (size_ >= capacity_)
{
reserve(capacity_ * reserve_miltiply_);
}
data_[size_++] = std::move(value);
}

void pop_back() {
if (size_ == 0)
throw std::out_of_range("empty vector");
data_[--size_] = T();
}

void clear() {
while (size_ > 0)
{
pop_back();
}
}

void reserve(size_type new_size) {
if (new_size <= capacity_)
return;

T* new_data = new T[new_size];
for (size_type i = 0; i < size_; ++i)
{
new_data[i] = std::move(data_[i]);
}
delete[] data_;

data_ = new_data;
capacity_ = new_size;
}

void resize(size_type new_size) {
if (new_size < size_)
{
while (size_ > new_size)
{
pop_back();
}
}
else if (new_size > size_)
{
reserve(new_size);
while (size_ < new_size)
{
data_[size_++] = T();
}
}
}

iterator begin() const noexcept {
return iterator(data_);
}

iterator end() const noexcept {
return Iterator(data_ + size_);
}

size_type size() const noexcept {
return size_;
}

size_type capacity() const noexcept {
return capacity_;
}

bool empty() const noexcept {
return size_ == 0;
}

private:
pointer data_;
size_type size_;
size_type capacity_;
};
