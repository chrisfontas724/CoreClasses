#include <gtest/gtest.h>
#include "threading/dispatch_queue.hpp"
#include <stdio.h>

namespace cfx {

TEST(Dispatch, SerialTest) {
    DispatchQueue queue(5, true);
    uint32_t count = 90;

    auto decrement = [&count](){ count--; };
    auto increment = [&count](){ count++; };
    for (uint32_t i = 0; i < 90; i++) {
        queue.dispatch(decrement);
    }
    queue.wait();
    EXPECT_EQ(queue.num_jobs(), 0);
    EXPECT_EQ(count, 0);

    for (uint32_t i = 0; i < 90; i++) {
        queue.dispatch(increment);
    }

    queue.wait();
    EXPECT_EQ(queue.num_jobs(), 0) << queue.num_jobs();
    EXPECT_EQ(count, 90);
}   

} // cfx