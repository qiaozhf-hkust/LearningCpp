#include <cstdio>

template<typename Resource, typename Deleter>
class UniqueResource {
public:
    explicit UniqueResource(Resource resource, Deleter deleter) noexcept : resource_(resource), deleter_(deleter) {}
    ~UniqueResource() { 
        if (resource_) deleter_(resource_); 
    }
    
    UniqueResource(const Resource& resource) = delete;
    Resource& operator=(const Resource& resource) = delete;

    Resource get() const noexcept { return resource_; }
private:
    Resource resource_;
    Deleter deleter_;
};

struct file_closer {
    void operator()(FILE* f) { 
        if (f){
            std::fclose(f);
        }
    }
};

using FileHandler = UniqueResource<FILE*, file_closer>;

FileHandler open(const char* path, const char* mode){
    return FileHandler(std::fopen(path, mode), file_closer{});
}