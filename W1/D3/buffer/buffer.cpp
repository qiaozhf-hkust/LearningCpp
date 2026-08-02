#include "buffer.h"
#include <print>
using std::println;

// buffer1
Buffer1::Buffer1(size_t size): size_(size), array_(new char[size]) {
    println("Construct Buffer1 with explicit constructor, counter={}", constuct_counter_++);
}

Buffer1::Buffer1(Buffer1&& buffer) noexcept: size_(buffer.size_), array_(buffer.array_) {
    buffer.array_ = nullptr;
    buffer.size_ = 0;
    println("Construct Buffer1 with move constructor, counter={}", move_counter_++);
}

Buffer1::Buffer1(const Buffer1& buffer): size_(buffer.size_), array_(new char[buffer.size_]) {
    std::copy_n(buffer.array_, buffer.size_, array_);
    println("Construct Buffer1 with copy constructor, counter={}", copy_counter_++);
}

Buffer1::~Buffer1(){
    delete[] array_;
}

// buffer2
Buffer2::Buffer2(size_t size): size_(size), array_(new char[size]) {
    println("Construct Buffer2 with explicit constructor, counter={}", constuct_counter_++);
}

Buffer2::Buffer2(Buffer2&& buffer): size_(buffer.size_), array_(buffer.array_) {
    buffer.array_ = nullptr;
    buffer.size_ = 0;
    println("Construct Buffer2 with move constructor, counter={}", move_counter_++);
}

Buffer2::Buffer2(const Buffer2& buffer): size_(buffer.size_), array_(new char[buffer.size_]) {
    std::copy_n(buffer.array_, buffer.size_, array_);
    println("Construct Buffer2 with copy constructor, counter={}", copy_counter_++);
}

Buffer2::~Buffer2(){
    delete[] array_;
}

// buffer3
Buffer3::Buffer3(size_t size): size_(size), array_(new char[size]) {
    println("Construct Buffer3 with explicit constructor, counter={}", constuct_counter_++);
}

Buffer3::Buffer3(const Buffer3& buffer): size_(buffer.size_), array_(new char[buffer.size_]) {
    std::copy_n(buffer.array_, buffer.size_, array_);
    println("Construct Buffer3 with copy constructor, counter={}", copy_counter_++);
}

Buffer3::~Buffer3(){
    delete[] array_;
}