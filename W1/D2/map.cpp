#include <map>
#include <string>
#include <print>

int main() {
    std::map<std::string, int> stringMapping;
    std::println("size of map: {}", stringMapping.size());
    auto a = stringMapping["test"];
    std::println("size of map: {}", stringMapping.size());
    std::println("a = {}", a);
    return 0;
}