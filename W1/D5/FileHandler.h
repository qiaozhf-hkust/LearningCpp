#include <cstdio>

class FileHandler {
public:
    explicit FileHandler(FILE* f) noexcept : f_(f) {};
    
    ~FileHandler() { 
        if (f_) std::fclose(f_); 
    }

    // no copy and no assign
    FileHandler(const FileHandler& fileHanlder) = delete;
    FileHandler& operator=(const FileHandler& fileHandler) = delete;

    FILE* get() const noexcept { return f_; }
private:
    FILE* f_;

};