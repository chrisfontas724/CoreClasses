#include <iostream>
#include "logging.hpp"
INITIALIZE_EASYLOGGINGPP

// Program entry point.
int main(int argc, char** argv) {
	START_EASYLOGGINGPP(argc, argv);
    CXL_LOG(INFO) << "Hello, useful utils =)";

	return 0;
}
