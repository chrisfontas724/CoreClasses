// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef DALI_GEOMETRY_TRANSFORM_HPP_
#define DALI_GEOMETRY_TRANSFORM_HPP_

#include "types.hpp"
#include "math_functions.hpp"

namespace cxl {

class Transform {
public:

    Transform()
    : translation_(0.0)
    , scale_(1.0)
    , rotation_(0,0,0,0)
    , rot_x_(0)
    , rot_y_(0)
    , rot_z_(0)
    {}

    Transform(vec3 translation, vec3 scale, quat rotation);
    
    // Updates the current position by the given values
    void translate(float x, float y, float z);
        
    // Resets the current position to be this value
    void setPosition(const vec3& translation);

    void setScale(const vec3& scale);
    void setUniformScale(float s);

    void rotate(float x, float y, float z);
    void setRotation(float x, float y, float z);

    const vec3& translation() const { return translation_; }
    const vec3& scale() const { return scale_; }
    const quat& rotation() const { return rotation_; }
    
    vec3 euler_angles() const {
        return vec3(rot_x_, rot_y_, rot_z_);
    }

    const mat4 matrix() const;


    Transform operator+(const Transform& t);
    Transform operator+=(const Transform& t);
    friend Transform operator+(const Transform& a, const Transform& b);
private:
    vec3 translation_;
    vec3 scale_;
    quat rotation_;
    float rot_x_;
    float rot_y_;
    float rot_z_;
};

inline Transform Transform::operator+(const Transform& t) {
    vec3 trans = translation_ + t.translation_;
    vec3 scale = scale_ * t.scale_;
    vec3 euler = euler_angles() + t.euler_angles();
    return Transform(trans, scale, glm::quat(euler * math::kDegreesToRadians));
}
    
inline Transform Transform::operator+=(const Transform &t) {
    translation_ += t.translation_;
    scale_ *= t.scale_;
    vec3 euler =  euler_angles() + t.euler_angles();
    rotation_  = glm::quat(euler * math::kDegreesToRadians);
        
    return *this;
}
    
inline Transform operator+(const Transform &a, const Transform &b) {
    Transform result;
    result.translation_ = a.translation_ + b.translation_;
    result.scale_ = a.scale_ * b.scale_;
    vec3 euler =  a.euler_angles() + b.euler_angles();
    result.rotation_  = glm::quat(euler * math::kDegreesToRadians);    return result;
}

} // cxl 

#endif // DALI_GEOMETRY_TRANSFORM_HPP_