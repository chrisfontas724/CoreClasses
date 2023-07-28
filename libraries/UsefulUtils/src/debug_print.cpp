#include "debug_print.hpp"
#include "bounding_box.hpp"

namespace geom {

std::ostream& operator<<(std::ostream& str, const glm::ivec2& v) {
    return str<< "ivec2[" << v.x << ", " << v.y << "]";
}

std::ostream& operator<<(std::ostream& str, const glm::vec2& v) {
    return str<< "vec2[" << v.x << ", " << v.y << "]";
}

std::ostream& operator<<(std::ostream& str, const glm::vec3& v) {
    return str << "vec3[" << v.x << ", " << v.y << ", " << v.z << "]";
}

std::ostream& operator<<(std::ostream& str, const glm::vec4& v) {
    return str << "vec4[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
}

std::ostream& operator<<(std::ostream& str, const glm::mat4& m) {
    return str << "mat4[" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << "\n" 
              <<  "     " << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << "\n" 
              <<  "     " << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << "\n" 
              <<  "     " << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << "]"; 
}

std::ostream& operator<<(std::ostream& str, const cxl::BoundingBox& bbox) {
    return str << "BoundingBox[" << ".min = " << bbox.min() << ", "
                                  << ".max = " << bbox.max();
}

}
