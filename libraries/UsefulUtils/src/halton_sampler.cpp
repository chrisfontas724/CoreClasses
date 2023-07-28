#include "halton_sampler.hpp"
#include "logging.hpp"
#include <math.h>

namespace cxl {

namespace {

 // Simple function which efficiently reverses the bits in a given unsigned int.
 // However, this method assumes that the integer provided has 32 bits and
 // thus will not work on machines that use a different integer representation
uint32_t reverseBits(uint32_t n) {
    n = (n << 16) | (n >> 16);
    
    n = ((n & 0x00ff00ff) << 8) | ((n & 0xff00ff00) >> 8);
    
    n = ((n & 0x0f0f0f0f) << 4) | ((n & 0xf0f0f0f0) >> 4);
    
    n = ((n & 0x33333333) << 2) | ((n & 0xcccccccc) >> 2);
    
    n = ((n & 0x55555555) << 1) | ((n & 0xaaaaaaaa) >> 1);
    
    return n;
}

// For a radical inverse with base 2, we can optimize the conversion using
// bit shifts. All one has to do is reverse the bits in the number and
// All one has to do is reverse the bits in
// multiply by 2^-32.
float radicalInverse2(uint32_t num) {
    num = reverseBits(num);
    float inv2To32 = 1.0f / (1ul << 32);
    return num * inv2To32;
}

// This is the general function used to find the radical inverse of a number
// given a base b. This function is only used for bases other than 2, as base
// 2 can be optimized using bit inversion.
float radicalInverseB(uint32_t num, uint32_t b) {
    float result = 0.f;
    float invB = 1.0f / b;
    float invPowB = 1.0f;
    uint32_t max = static_cast<uint32_t>(logf(static_cast<float>(num))
                  / logf(static_cast<float>(b)) + 1);  
    
    for (uint32_t i = 1; i <= max; i++) {
        uint32_t digit = static_cast<uint32_t>(num * invPowB) % b;
        invPowB *= invB;
        result += digit * invPowB;
    }
    return result;
}
} // namespace


// Creates a vector of samples for a unit square using the Halton Sequence
// algorithm in 2 dimensions. The coordinates for each dimension are chosen
// by finding the radical inverses of a set of numbers given for specific
// bases. A radical inverse is found by converting a decimal number to a
// specific base, finding the inverse of the number in that base by flipping
// the digits across the decimal point and then converting the number back
// into decimal form.
 //
vec2 HaltonSampler::next() {
    float inverse1 = (base1_ == 2) ? radicalInverse2(index_) : radicalInverseB(index_, base1_);
    float inverse2 = (base2_ == 2) ? radicalInverse2(index_) : radicalInverseB(index_, base2_);
    index_++;
    CXL_DCHECK(inverse1 >=0 && inverse2 >= 0);
    CXL_DCHECK(inverse1 <=1 && inverse2 <= 1);
    return vec2(inverse1, inverse2);
}

// Sets the index back to 0
void HaltonSampler::reset() {
    index_ = 0;
}

} // cxl