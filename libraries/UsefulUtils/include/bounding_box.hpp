// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef GEOMETRY_BOUNDING_BOX_HPP_
#define GEOMETRY_BOUNDING_BOX_HPP_

#include "types.hpp"

namespace cxl {

// Axis-aligned bounding box.
class BoundingBox {
public:
    
    // No error checking - is up to the caller
    // to ensure that |max| is larger than |min|.
    BoundingBox(vec4 min, vec4 max);

    // Empty bounding box denoted by the fact
    // that the max point is larger than the
    // min point.
    BoundingBox() 
    : min_(vec4(1,1,1,1))
    , max_(vec4(0,0,0,1))
    {}

    bool operator==(const BoundingBox& b) const {
        return equals(min_, b.min_) && equals(max_, b.max_);
    }

    bool operator!=(const BoundingBox& b) const {
        return !(*this == b);
    }

    bool is_empty() const { return *this == BoundingBox(); }

    // Getters.
    const vec4& min() const { return min_; }
    const vec4& max() const { return max_; }
    vec4 span() const { return max_ - min_; }

    // Checks to see if the specified point is contained
    // within the bounding box.
    bool contains(vec4 v) const;
    
    // Expands the bounding box to include the given point.
    void incorporate(vec4 v);

    // Combines the two bounding boxes together to create
    // a new box which incorporates the original two.
    void combine(const BoundingBox& b2);
        
private:
    vec4 min_, max_;
};

DEBUG_PRINTABLE(BoundingBox)

} // cxl

#endif // GEOMETRY_BOUNDING_BOX_HPP_