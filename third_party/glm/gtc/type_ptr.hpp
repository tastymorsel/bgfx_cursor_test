#pragma once

#include "../glm.hpp"

namespace glm {
    // Value pointer functions for vectors
    template<typename T, int N>
    T* value_ptr(vec<T, N>& v) {
        return v.value_ptr();
    }
    
    template<typename T, int N>
    const T* value_ptr(const vec<T, N>& v) {
        return v.value_ptr();
    }
    
    // Value pointer functions for matrices
    template<typename T, int N>
    T* value_ptr(mat<T, N>& m) {
        return m.value_ptr();
    }
    
    template<typename T, int N>
    const T* value_ptr(const mat<T, N>& m) {
        return m.value_ptr();
    }
}