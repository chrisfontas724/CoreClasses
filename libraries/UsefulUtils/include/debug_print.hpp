// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef GEOMETRY_UTIL_DEBUG_PRINT_HPP_
#define GEOMETRY_UTIL_DEBUG_PRINT_HPP_

#include <ostream>

#define DEBUG_PRINTABLE(X) std::ostream& operator<<(std::ostream& str, const X&);

#endif // GEOMETRY_UTIL_DEBUG_PRINT_HPP_