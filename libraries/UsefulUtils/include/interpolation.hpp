// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef GEOMETRY_UTIL_INTERPOLATION_HPP_
#define GEOMETRY_UTIL_INTERPOLATION_HPP_

#include "math_functions.hpp"
#include "types.hpp"

namespace interpolation {
    inline float __linearInterpolation(float a, float b, float t) {
        return ((float)(1.0) - t) * a   + t*b;
    }
        
    inline float __cosineInterpolation(float a, float b, float t) {
        float ft = t*3.14159265f;
        float f = ((float)(1.0) - cos(ft)) * (float)(0.5);
        return a*((float)(1.0)-f)+b*f;
    }
        
    template<typename T>
    inline T __linear(const T &a, const T &b, float t) {
        return (1.f - t)*a + t*b;
    }
        
    template<>
    inline glm::quat __linear(const glm::quat& a, const glm::quat& b, float t) {
        return glm::mix(a,b,t);
    }
} // interpolation

#endif // GEOMETRY_UTIL_INTERPOLATION_HPP_
