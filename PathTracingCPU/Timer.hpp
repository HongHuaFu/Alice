#pragma once
#include <PathTracingCPU/Core.hpp>
#include <chrono>
#include <iomanip>

namespace Alice::PathTracingCPU 
{
    // 简单时间计数器
    class Timer 
    {
    public:
        Timer() { Reset(); }
        void Reset() { start = std::chrono::system_clock::now(); }

        /// 返回启动到当前时间
        double Elapsed() const 
        {
            auto now = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
            return (double)duration.count();
        }

        /// 返回规格化后的启动时间
        std::string ElapsedString(bool precise = false) const 
        {
            return timeString(Elapsed(), precise);
        }

        /// 返回启动到当前时间并且重置计数器
        double Lap() 
        {
            auto now = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
            start = now;
            return (double)duration.count();
        }

        /// 返回规格化的启动到当前时间并且重置计数器
        std::string LapString(bool precise = false) 
        {
            return timeString(Lap(), precise);
        }

    private:
        std::chrono::system_clock::time_point start;

        inline static std::string timeString(double time, bool precise)
        {
            if (std::isnan(time) || std::isinf(time))
                return "inf";

            std::string suffix = "ms";
            if (time > 1000) {
                time /= 1000; suffix = "s";
                if (time > 60) {
                    time /= 60; suffix = "m";
                    if (time > 60) {
                        time /= 60; suffix = "h";
                        if (time > 12) {
                            time /= 12; suffix = "d";
                        }
                    }
                }
            }

            std::ostringstream os;
            os << std::setprecision(precise ? 4 : 1)
                << std::fixed << time << suffix;

            return os.str();
        }
    };

}