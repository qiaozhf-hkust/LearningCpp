#include<print>
#include<vector>
#include "buffer.h"
using std::vector;
using std::println;

int main() {
    Buffer1 buffer1(10);
    auto buffer1Copy1 = Buffer1(1);
    auto buffer1Copy2 = buffer1;

    println("Vector Push Back...");
    auto vec = vector<Buffer1>();
    for(std::size_t i=0; i<5; i++){
        println("Vector Push Back: {}", i);
        vec.push_back(Buffer1(1));
    }

    vec.clear();
    vec.shrink_to_fit();
    for(std::size_t i=0; i<5; i++){
        println("Vector Push Back: {}", i);
        vec.push_back(std::move(Buffer1(1)));
    }

    println("Vector Emplace Back...");
    for(std::size_t i=0; i<10; i++){
        println("Vector Emplace Back: {}", i);
        vec.emplace_back(1);
    }

    Buffer2 buffer2(10);
    auto buffer2Copy = buffer2;
    auto buffer2Copy2 = Buffer2(1);

    println("Vector Push Back...");
    auto vec2 = vector<Buffer2>();
    for(std::size_t i=0; i<5; i++){
        println("Vector Push Back: {}", i);
        vec2.push_back(Buffer2(1));
    }
    
    println("Vector Emplace Back...");
    for(std::size_t i=0; i<10; i++){
        println("Vector Emplace Back: {}", i);
        vec2.emplace_back(1);
    }

    Buffer3 buffer3(10);
    auto buffer3Copy = buffer3;
    auto buffer3Copy2 = Buffer3(1);

    println("Vector Push Back...");
    auto vec3 = vector<Buffer3>();
    for(std::size_t i=0; i<5; i++){
        println("Vector Push Back: {}", i);
        vec3.push_back(Buffer3(1));
    }

    println("Vector Emplace Back...");
    for(std::size_t i=0; i<10; i++){
        println("Vector Emplace Back: {}", i);
        vec3.emplace_back(1);
    }
}