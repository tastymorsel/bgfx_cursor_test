#pragma once

#include "../glm.hpp"

namespace glm {
    // Matrix transformation functions
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
    
    // Additional transformation functions
    template<typename T>
    mat<T, 4> perspective(T fovy, T aspect, T near, T far) {
        mat<T, 4> result;
        T f = 1.0f / tan(fovy * 0.5f);
        result(0, 0) = f / aspect;
        result(1, 1) = f;
        result(2, 2) = (far + near) / (near - far);
        result(2, 3) = (2.0f * far * near) / (near - far);
        result(3, 2) = -1.0f;
        return result;
    }
    
    template<typename T>
    mat<T, 4> ortho(T left, T right, T bottom, T top, T near, T far) {
        mat<T, 4> result;
        result(0, 0) = 2.0f / (right - left);
        result(1, 1) = 2.0f / (top - bottom);
        result(2, 2) = -2.0f / (far - near);
        result(0, 3) = -(right + left) / (right - left);
        result(1, 3) = -(top + bottom) / (top - bottom);
        result(2, 3) = -(far + near) / (far - near);
        result(3, 3) = 1.0f;
        return result;
    }
}