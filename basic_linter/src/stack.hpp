#pragma once

#include <vector>

template<typename T>
class SimpleStack {
private:
    std::vector<T> data;

public:
    void push(const T& value) {
        data.push_back(value);
    }
    
    void pop() {
        if (!data.empty()) {
            data.pop_back();
        }
    }
    
    T& top() {
        return data.back();
    }
    
    const T& top() const {
        return data.back();
    }
    
    bool empty() const {
        return data.empty();
    }
    
    size_t size() const {
        return data.size();
    }
};
