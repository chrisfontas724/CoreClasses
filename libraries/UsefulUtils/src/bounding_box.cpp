#include "bounding_box.hpp"
#include "logging.hpp"

namespace cxl {

BoundingBox::BoundingBox(vec4 min, vec4 max) {
#ifndef NDEBUG
    CXL_CHECK(max.x >= min.x);
    CXL_CHECK(max.y >= min.y);
    CXL_CHECK(max.z >= min.z);
#endif // NDEBUG
    min_ = min;
    max_ = max;
}

bool BoundingBox::contains(vec4 v) const {
    if (is_empty()) return false;
    if (v.x < min_.x || v.x > max_.x) return false;
    if (v.y < min_.y || v.y > max_.y) return false;
    if (v.z < min_.z || v.z > max_.z) return false;
    return true;
}

void BoundingBox::incorporate(vec4 v) {
    min_.x = glm::min(min_.x, v.x);    
    min_.y = glm::min(min_.y, v.y);
    min_.z = glm::min(min_.z, v.z);

    max_.x = glm::max(min_.x, v.x);    
    max_.y = glm::max(min_.y, v.y);
    max_.z = glm::max(min_.z, v.z);
}

void BoundingBox::combine(const BoundingBox& b) {

}

} // cxl