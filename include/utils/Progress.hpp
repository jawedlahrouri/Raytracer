#ifndef PROGRESS_HPP_
#define PROGRESS_HPP_

#include <chrono>
#include <mutex>

namespace Raytracer {
    class Progress {
        public:
            static void monitor(
                std::chrono::steady_clock::time_point startTime,
                const int& current,
                int total,
                const bool& finished,
                std::mutex& mutex
            );
    };
}

#endif /* !PROGRESS_HPP_ */
