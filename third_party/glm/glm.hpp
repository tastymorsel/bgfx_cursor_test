#pragma once

#include <cmath>

namespace glm {
    // Basic vector types
    template<typename T, int N>
    struct vec {
        T data[N];
        
        vec() { for(int i = 0; i < N; ++i) data[i] = T(0); }
        vec(T x) { for(int i = 0; i < N; ++i) data[i] = x; }
        vec(T x, T y) { data[0] = x; data[1] = y; if(N > 2) data[2] = T(0); if(N > 3) data[3] = T(1); }
        vec(T x, T y, T z) { data[0] = x; data[1] = y; data[2] = z; if(N > 3) data[3] = T(1); }
        vec(T x, T y, T z, T w) { data[0] = x; data[1] = y; data[2] = z; data[3] = w; }
        
        T& operator[](int i) { return data[i]; }
        const T& operator[](int i) const { return data[i]; }
        
        T& x() { return data[0]; }
        T& y() { return data[1]; }
        T& z() { return data[2]; }
        T& w() { return data[3]; }
        
        const T& x() const { return data[0]; }
        const T& y() const { return data[1]; }
        const T& z() const { return data[2]; }
        const T& w() const { return data[3]; }
    };
    
    using vec2 = vec<float, 2>;
    using vec3 = vec<float, 3>;
    using vec4 = vec<float, 4>;
    
    // Matrix types
    template<typename T, int N>
    struct mat {
        T data[N * N];
        
        mat() { 
            for(int i = 0; i < N * N; ++i) data[i] = T(0);
            for(int i = 0; i < N; ++i) data[i * N + i] = T(1);
        }
        
        T& operator()(int row, int col) { return data[row * N + col]; }
        const T& operator()(int row, int col) const { return data[row * N + col]; }
        
        T* value_ptr() { return data; }
        const T* value_ptr() const { return data; }
    };
    
    using mat4 = mat<float, 4>;
    
    // Matrix construction functions
    template<typename T>
    mat<T, 4> translate(const mat<T, 4>& m, const vec<T, 3>& v) {
        mat<T, 4> result = m;
        result(0, 3) += v[0];
        result(1, 3) += v[1];
        result(2, 3) += v[2];
        return result;
    }
    
    template<typename T>
    mat<T, 4> rotate(const mat<T, 4>& m, T angle, const vec<T, 3>& axis) {
        // Simplified rotation - just return the matrix for now
        return m;
    }
    
    template<typename T>
    mat<T, 4> scale(const mat<T, 4>& m, const vec<T, 3>& v) {
        mat<T, 4> result = m;
        result(0, 0) *= v[0];
        result(1, 1) *= v[1];
        result(2, 2) *= v[2];
        return result;
    }
    
    // Value pointer function
    template<typename T, int N>
    T* value_ptr(const vec<T, N>& v) {
        return const_cast<T*>(v.data);
    }
    
    template<typename T, int N>
    T* value_ptr(const mat<T, N>& m) {
        return const_cast<T*>(m.data);
    }
}