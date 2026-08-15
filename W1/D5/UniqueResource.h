template<typename Resource>
class UniqueResource {
public:
    explicit UniqueResource(Resource resource) noexcept : resource_(resource) {}
    ~UniqueResource() { 
        if (resource_) release(resource_); 
    }
    
    UniqueResource(const Resource& resource) = delete;
    Resource& operator=(const Resource& resource) = delete;

    Resource get() const noexcept { return resource_; }
private:
    Resource resource_;
    void release(); // ?
};