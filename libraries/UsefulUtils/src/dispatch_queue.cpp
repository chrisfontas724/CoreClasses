#include "dispatch_queue.hpp"
#include "logging.hpp"

namespace cfx {
DispatchQueue::DispatchQueue(uint32_t num_threads, bool is_serial) 
: threads_(num_threads) 
, is_serial_(is_serial)
, num_busy_(0) {
	for(size_t i = 0; i < threads_.size(); i++) {
		threads_[i] = std::thread(&DispatchQueue::dispatch_thread_handler, this);
	}
}

DispatchQueue::~DispatchQueue() {
	CXL_VLOG(9) << "Destructor: Destroying dispatch threads...";

	// Signal to dispatch threads that it's time to wrap up.
	std::unique_lock<std::mutex> lock(lock_);
	quit_ = true;
	lock.unlock();
	cv_.notify_all();

	// Wait for all threads to finish before exiting.
	for(size_t i = 0; i < threads_.size(); i++) {
		if (threads_[i].joinable()) {
			CXL_VLOG(9) << "Destructor: Joining thread " << i << "until completion";
			threads_[i].join();
		}
	}
}

void DispatchQueue::dispatch(const Function& func) {
	std::unique_lock<std::mutex> lock(lock_);
	q_.push(func);

	// Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again.
	lock.unlock();
	cv_.notify_all();
}

void DispatchQueue::dispatch(Function&& func) {
	std::unique_lock<std::mutex> lock(lock_);
	q_.push(std::move(func));

	// Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again.
	lock.unlock();
	cv_.notify_all();
}

void DispatchQueue::dispatch_thread_handler(void) {
	std::unique_lock<std::mutex> lock(lock_);

	do {
		//Wait until we have data or a quit signal
		cv_.wait(lock, [this]{
			return (q_.size() || quit_);
		});

		//after wait, we own the lock
		if (!quit_ && q_.size()) {
			auto func = std::move(q_.front());
			q_.pop();

			//unlock now that we're done messing with the queue.
			num_busy_++;
			lock.unlock();

			if (is_serial_) {
				serial_lock_.lock();
			}

			// Execute the work item.
			func();

			if (is_serial_) {
				serial_lock_.unlock();
			}

			lock.lock();
			num_busy_--;
            task_completion_.notify_one();
		}
	} while (!quit_);
}

void DispatchQueue::wait() {
    std::unique_lock<std::mutex> lock(lock_);
	CXL_DCHECK(lock) << "Bad lock";

    // Block until no pending tasks remain and all workers are idle.
    task_completion_.wait(lock, [this]() { 
        return q_.empty() && num_busy_ == 0; 
    });
}

uint32_t DispatchQueue::num_jobs() {
    std::unique_lock<std::mutex> lock(lock_);
    return q_.size();
}

} // cfx