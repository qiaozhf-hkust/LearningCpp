#include <cstdio>
#include <utility>

template<typename Resource, typename Deleter>
class UniqueResource {
public:
    explicit UniqueResource(Resource resource, Deleter deleter) noexcept : resource_(resource), deleter_(deleter) {}
    ~UniqueResource() { 
        if (resource_) deleter_(resource_); 
    }
    
    UniqueResource(Resource&& resource) noexcept :
        resource_(resource.resource_), 
        deleter_(std::move(resource.deleter_)) {
            resource.resouce_ = {};
    }

    Resource& operator=(Resource&& resource) noexcept {
        if (&resource != this){
            if (resource_) { deleter_(resource_); }
            resource_ = resource.resource_;
            deleter_ = std::move(resource.deleter_);
            resource.resource_ = Resource{};
        }
        return *this;
    }

    UniqueResource(const Resource& resource) = delete;
    Resource& operator=(const Resource& resource) = delete;

    Resource get() const noexcept { return resource_; }
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