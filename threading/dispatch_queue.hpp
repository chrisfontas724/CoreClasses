// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef CORE_THREADING_DISPATCH_QUEUE_HPP_
#define CORE_THREADING_DISPATCH_QUEUE_HPP_

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>

namespace cfx {

// A simple dispatch queue for executing work items
// on multiple threads. 
class DispatchQueue {
    typedef std::function<void(void)> Function;
public:

    DispatchQueue(uint32_t num_threads = 1, bool is_serial=false);
    ~DispatchQueue();

    void dispatch(const Function& func);
	void dispatch(Function&& func);

    // Wait for all work items to complete. This blocks the
    // calling thread.
    void wait();

    uint32_t num_jobs();

    // Delete copy and assign operations.
	DispatchQueue(const DispatchQueue& rhs) = delete;
	DispatchQueue& operator=(const DispatchQueue& rhs) = delete;
	DispatchQueue(DispatchQueue&& rhs) = delete;
	DispatchQueue& operator=(DispatchQueue&& rhs) = delete;
private:

	std::mutex lock_;
    std::mutex serial_lock_;
	std::vector<std::thread> threads_;
	std::queue<Function> q_;
	std::condition_variable cv_;
    std::condition_variable task_completion_;
    uint32_t num_busy_ = 0;
    bool is_serial_;
	bool quit_ = false;

	void dispatch_thread_handler(void);
};
} // cfx

#endif // CORE_THREADING_DISPATCH_QUEUE_HPP_