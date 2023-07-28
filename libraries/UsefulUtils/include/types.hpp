// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef GEOMETRY_UTIL_TYPES_HPP_
#define GEOMETRY_UTIL_TYPES_HPP_

#define GLM_ENABLE_EXPERIMENTAL

// Note on defining GLM_FORCE_DEFAULT_ALIGNNED_GENTYPES:
// This term will have glm take care of most alignment issues for us.
// However, the Vulkan rules for alignment are copied and pasted here
// for reference in case of an edge case that GLM does not handle.
// 
// RULES:
// - Scalars have to be aligned by N (= 4 bytes given 32 bit floats).
// -  A vec2 must be aligned by 2N (= 8 bytes)
// -  A vec3 or vec4 must be aligned by 4N (= 16 bytes)
// -  A nested structure must be aligned by the base alignment of its members rounded up to a multiple of 16.
// -  A mat4 matrix must have the same alignment as a vec4.
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include "debug_print.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/ext/matrix_relational.hpp>
#include <cstdint>

namespace cxl {

static constexpr float kEpsilon = 0.0000001;
static constexpr float kPi = 3.14159265;
static constexpr float kTwoPi = 2.f * kPi;

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

typedef glm::ivec2 ivec2;
typedef glm::ivec4 ivec4;

typedef glm::mat4 mat4;
typedef glm::quat quat;


inline bool equals(glm::mat4 const& A, glm::mat4 const& B) {
    glm::bvec4 const ColumnEqual = glm::equal(A, B, kEpsilon); // Evaluation per column
    return glm::all(ColumnEqual);
}

inline bool equals(glm::vec4 const& A, glm::vec4 const& B) {
    return glm::all(glm::epsilonEqual(A, B, kEpsilon));
}

template<typename T>
struct TypeParseTraits;

// Allows for run-time reflection on registered types.
#define REGISTER_PARSE_TYPE(X)                      \
    template <> struct TypeParseTraits<X>           \
    { static const char* name() { return #X; } };   \

REGISTER_PARSE_TYPE(vec2);
REGISTER_PARSE_TYPE(vec3);
REGISTER_PARSE_TYPE(vec4);
REGISTER_PARSE_TYPE(mat4);
REGISTER_PARSE_TYPE(int32_t);
REGISTER_PARSE_TYPE(uint32_t);
REGISTER_PARSE_TYPE(float);
REGISTER_PARSE_TYPE(short);

DEBUG_PRINTABLE(vec2);
DEBUG_PRINTABLE(vec3);
DEBUG_PRINTABLE(vec4);
DEBUG_PRINTABLE(ivec2);
DEBUG_PRINTABLE(mat4);
} // cxl

#endif // GEOMETRY_UTIL_TYPES_HPP_
