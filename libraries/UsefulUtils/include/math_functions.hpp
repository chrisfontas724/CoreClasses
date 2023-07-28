// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef MATH_FUNCTIONS_HPP_
#define MATH_FUNCTIONS_HPP_

#include <cstdint>
#include <cmath>
#include <math.h> 
#include <utility>

namespace math{

    static const float kEpsilon = 0.0001f;
    static const double kEpsilonD = 0.000001f;
    
    static const float kDegreesToRadians = 0.0174533f;

    // Functions.
    inline float __abs(float value) { return float(::fabs(value));  }
    inline double __abs(double value) { return double(::fabs(value)); }

    inline float __sqrt(float value) { return float(::sqrtf(value)); }
    inline double __sqrt(double value) { return double(::sqrt(value)); }

    inline float __sin(float value)                     { return float(::sinf(value)); }
    inline double __sin(double value)                   { return double(::sin(value)); }

    inline float __cos(float value)                     { return float(::cosf(value)); }
    inline double __cos(double value)                   { return double(::cos(value)); }
        
    inline float __tan(float value)                     { return float(::tanf(value)); }
    inline double __tan(double value)                   { return double(::tan(value)); }
        
    inline float __asin(float value)                    { return float(::asinf(value)); }
    inline double __asin(double value)                  { return double(::asin(value)); }
        
    inline float __acos(float value)                    { return float(::acosf(value)); }
    inline double __acos(double value)                  { return double(::acos(value)); }
        
    inline float __atan(float value)                    { return float(::atan(value));  }
    inline double __atan(double value)                  { return double(::atan(value)); }
        
    inline float __atan2(float a, float b)              { return float(::atan2f(a, b)); }
    inline double __atan2(double a, double b)           { return double(::atan2(a, b)); }

    template<class T>
    T max(T a, T b) {
        return a > b ? a : b;
    }
        
    template<class T>
    inline T min(T a, T b) {
        return a < b ? a : b;
    }

    template<class T>
    inline void swap(T &a, T &b) {
        a = a + b;
        b = a - b;
        a = a - b;
    }
        
    template<class T>
    inline T clamp(T a, T min, T max) {
        if (a < min) return min;
        if (a > max) return max;
        return a;
    }

    inline float epsilonCheck(float a) {
        return (__abs(a) <= kEpsilon) ? 0.f : a;
    }
        
    inline bool equal(float a, float b) {
        return __abs(a - b) <= kEpsilon;
    }

    template<typename T>
    inline T round(T num, T base) {
       return (num + base - 1) / base;
    }
} // math

#endif // MATH_FUNCTIONS_HPP_
