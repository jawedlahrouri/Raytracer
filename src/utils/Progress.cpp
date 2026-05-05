#include "utils/Progress.hpp"
#include <iostream>
#include <iomanip>
#include <thread>

namespace Raytracer {
    void Progress::monitor(
        std::chrono::steady_clock::time_point startTime,
        const int& current,
        int total,
        const bool& finished,
        std::mutex& mutex
    ) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            int currentVal;
            bool isDone;
            {
                std::lock_guard<std::mutex> lock(mutex);
                currentVal = current;
                isDone = finished;
            }
            
            if (currentVal > 0 && currentVal < total) {
                double progress = static_cast<double>(currentVal) / total;
                double totalEstimated = static_cast<double>(elapsed) / progress;
                double remaining = totalEstimated - elapsed;
                
                int remMin = static_cast<int>(remaining) / 60;
                int remSec = static_cast<int>(remaining) % 60;
                
                std::cout << "\rProgress: " << std::fixed << std::setprecision(1) << (progress * 100.0) << "% "
                        << "| Elapsed: " << elapsed << "s "
                        << "| ETA: " << remMin << "m " << remSec << "s    " << std::flush;
            }
            if (isDone)
                break;
        }
        auto endTime = std::chrono::steady_clock::now();
        auto totalElapsed = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
        std::cout << "\rRendering completed in " << totalElapsed << "s.                                      " << std::endl;
    }
}
