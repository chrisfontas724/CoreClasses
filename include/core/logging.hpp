// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef CORE_LOGGING_LOGGING_HPP_
#define CORE_LOGGING_LOGGING_HPP_

#include <core/easylogging++.h>

#define CXL_LOG(SEVERITY) LOG(SEVERITY)
#define CXL_VLOG(LEVEL) VLOG(LEVEL)
#define CXL_CHECK(CONDITION) CHECK(CONDITION)
#define CXL_DCHECK(CONDITION) DCHECK(CONDITION)
#define CXL_CHECK_EQ(COND1, COND2) CHECK_EQ(COND1, COND2)


#endif // CORE_LOGGING_LOGGING_HPP_
