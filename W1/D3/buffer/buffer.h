#include <cstddef>
using std::size_t;

// noexcept move construct + copy construct
class Buffer1 {
public:
    explicit Buffer1(size_t size);
    Buffer1(Buffer1&& buffer) noexcept;
    Buffer1(const Buffer1& buffer);
    ~Buffer1();

private:
    size_t size_{};
    char* array_{};
    inline static int constuct_counter_{0};
    inline static int move_counter_{0};
    inline static int copy_counter_{0};
};

// move construct + copy construct
class Buffer2 {
public:
    explicit Buffer2(size_t size);
    Buffer2(Buffer2&& buffer);
    Buffer2(const Buffer2& buffer);
    ~Buffer2();

private:
    size_t size_{};
    char* array_{};
    inline static int constuct_counter_{0};
    inline static int move_counter_{0};
    inline static int copy_counter_{0};
};

// copy construct only
class Buffer3 {
public:
    explicit Buffer3(size_t size);
    Buffer3(Buffer2&& buffer) = delete;
    Buffer3(const Buffer3& buffer);
    ~Buffer3();

private:
    size_t size_{};
    char* array_{};
    inline static int constuct_counter_{0};
    inline static int move_counter_{0};
    inline static int copy_counter_{0};
};