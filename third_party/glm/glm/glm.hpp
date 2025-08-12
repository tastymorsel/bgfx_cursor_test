#pragma once

#include <cmath>

namespace glm {
    // Basic vector types
    template<typename T, int N>
    struct vec {
        union {
            T data[N];
            struct {
                T x, y, z, w;
            };
        };
        
        vec() { for(int i = 0; i < N; ++i) data[i] = T(0); }
        vec(T x) { for(int i = 0; i < N; ++i) data[i] = x; }
        vec(T x, T y) { data[0] = x; data[1] = y; if(N > 2) data[2] = T(0); if(N > 3) data[3] = T(1); }
        vec(T x, T y, T z) { data[0] = x; data[1] = y; data[2] = z; if(N > 3) data[3] = T(1); }
        vec(T x, T y, T z, T w) { data[0] = x; data[1] = y; data[2] = z; data[3] = w; }
        
        T& operator[](int i) { return data[i]; }
        const T& operator[](int i) const { return data[i]; }
        
        // Vector operators
        vec operator+(const vec& other) const {
            vec result;
            for(int i = 0; i < N; ++i) result.data[i] = data[i] + other.data[i];
            return result;
        }
        
        vec operator-(const vec& other) const {
            vec result;
            for(int i = 0; i < N; ++i) result.data[i] = data[i] - other.data[i];
            return result;
        }
        
        vec operator-() const {
            vec result;
            for(int i = 0; i < N; ++i) result.data[i] = -data[i];
            return result;
        }
        
        vec operator*(T scalar) const {
            vec result;
            for(int i = 0; i < N; ++i) result.data[i] = data[i] * scalar;
            return result;
        }
        
        vec operator*(const vec& other) const {
            vec result;
            for(int i = 0; i < N; ++i) result.data[i] = data[i] * other.data[i];
            return result;
        }
        
        vec& operator+=(const vec& other) {
            for(int i = 0; i < N; ++i) data[i] += other.data[i];
            return *this;
        }
        
        vec& operator-=(const vec& other) {
            for(int i = 0; i < N; ++i) data[i] -= other.data[i];
            return *this;
        }
        
        vec& operator*=(T scalar) {
            for(int i = 0; i < N; ++i) data[i] *= scalar;
            return *this;
        }
        
        vec& operator*=(const vec& other) {
            for(int i = 0; i < N; ++i) data[i] *= other.data[i];
            return *this;
        }
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
        
        mat(T value) { 
            for(int i = 0; i < N * N; ++i) data[i] = T(0);
            for(int i = 0; i < N; ++i) data[i * N + i] = value;
        }
        
        T& operator()(int row, int col) { return data[row * N + col]; }
        const T& operator()(int row, int col) const { return data[row * N + col]; }
        
        T* value_ptr() { return data; }
        const T* value_ptr() const { return data; }
    };
    
    using mat4 = mat<float, 4>;
    
    // Utility functions
    template<typename T, int N>
    T length(const vec<T, N>& v) {
        T sum = T(0);
        for(int i = 0; i < N; ++i) sum += v.data[i] * v.data[i];
        return sqrt(sum);
    }
    
    template<typename T, int N>
    vec<T, N> normalize(const vec<T, N>& v) {
        T len = length(v);
        if(len > T(0)) {
            return v * (T(1) / len);
        }
        return v;
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