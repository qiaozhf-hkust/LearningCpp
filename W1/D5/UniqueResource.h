#include <cstdio>
#include <unistd.h>
#include <utility>

template<typename T>
struct default_resource_traits {
    static constexpr T invalid_value() noexcept { return T{}; }
};

struct fd_traits {
    static constexpr int invalid_value() noexcept { return -1; }
};

struct fd_closer {
    void operator()(int fd) const noexcept  {
        if (fd >= 0) ::close(fd);
    }
};

template<typename Resource, typename Deleter, typename Traits = default_resource_traits<Resource>>
class UniqueResource {
public:
    explicit UniqueResource(Resource resource, Deleter deleter) noexcept : resource_(resource), deleter_(deleter) {}
    ~UniqueResource() { 
        reset();
    }
    
    UniqueResource(Resource&& resource) noexcept :
        resource_(resource.resource_), 
        deleter_(std::move(resource.deleter_)) {
            resource.resouce_ = {};
    }

    Resource& operator=(Resource&& resource) noexcept {
        if (&resource != this){
            reset(resource.release());
            deleter_ = std::move(resource.deleter_);
        }
        return *this;
    }

    UniqueResource(const Resource& resource) = delete;
    Resource& operator=(const Resource& resource) = delete;

    Resource get() const noexcept { return resource_; }

    Resource release() noexcept {
        Resource tmp = resource_;
        resource_ = Traits::invalid_value();
        return tmp;
    }

    void reset() noexcept {
        if (resource_ != Traits::invalid_value()) {
            deleter_(resource_);
            resource_ = Traits::invalid_value();
        }
    }

    void reset(Resource r) {
        reset();
        resource_ = r;
    }

    explicit operator bool() const noexcept {
        return resource_ != Traits::invalid_value();
    } 

    Deleter& get_deleter() noexcept { return deleter_; }
    const Deleter& get_deleter() const noexcept { return deleter_; }

    friend void swap(UniqueResource& a, UniqueResource& b){
        using std::swap;
        swap(a.resource_, b.resource_);
        swap(a.deleter_, b.deleter_);
    }

private:
    Resource resource_;
    [[no_unique_address]] Deleter deleter_;
};

struct file_closer {
    void operator()(FILE* f) { 
        if (f){
            std::fclose(f);
        }
    }
};

// 创建别名方便使用
using FileHandler = UniqueResource<FILE*, file_closer>;

FileHandler open(const char* path, const char* mode){
    return FileHandler(std::fopen(path, mode), file_closer{});
}