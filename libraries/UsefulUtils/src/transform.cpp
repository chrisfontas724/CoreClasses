#include "transform.hpp"
#include <iostream> 

namespace cxl {

Transform::Transform(vec3 translation, vec3 scale, quat rotation)
: translation_(translation)
, scale_(scale)
, rotation_(rotation) {}


// Updates the current position by the given values
void Transform::translate(float x, float y, float z) {
    translation_ += glm::vec3(x,y,z);
}
        
// Resets the current position to be this value
void Transform::setPosition(const glm::vec3& translation) {
    translation_ = translation;
}

void Transform::setScale(const glm::vec3& scale) {
    scale_ = scale;
}

void Transform::setUniformScale(float s) {
    scale_ = glm::vec3(s);
}

void Transform::rotate(float x, float y, float z) {
    rot_x_ += x;
    rot_y_ += y;
    rot_z_ += z;
    rotation_ = glm::quat(glm::vec3(rot_x_, rot_y_, rot_z_) * math::kDegreesToRadians);
 }

void Transform::setRotation(float x, float y, float z) {
    rotation_ = glm::quat(0.0174533f*glm::vec3(x, y, z));
}

const glm::mat4 Transform::matrix() const {
    glm::mat4 translate = glm::translate(glm::mat4(1.0), translation_);
    glm::mat4 rotate = glm::toMat4(rotation_);
    glm::mat4 scale = glm::scale(scale_);
    return translate * rotate * scale;
}

} // cxl