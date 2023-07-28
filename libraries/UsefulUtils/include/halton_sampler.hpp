// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef DALI_GRAPHICS_SAMPLING_HALTON_SAMPLER_HPP_
#define DALI_GRAPHICS_SAMPLING_HALTON_SAMPLER_HPP_

#include "types.hpp"

namespace cxl {

class HaltonSampler {
public:

    HaltonSampler(uint32_t base1, uint32_t base2) 
    : base1_(base1)
    , base2_(base2)
    , index_(0) {}

    glm::vec2 next();

    void reset();

private:

    uint32_t index_;
    uint32_t base1_;
    uint32_t base2_;
};

} // cxl


#endif // DALI_GRAPHICS_SAMPLING_HALTON_SAMPLER_HPP_