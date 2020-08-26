#pragma once
#include <PathTracingCPU/Core.hpp>
#include <chrono>
#include <iomanip>

namespace Alice::PathTracingCPU 
{
    // ��ʱ�������
    class Timer 
    {
    public:
        Timer() { Reset(); }
        void Reset() { start = std::chrono::system_clock::now(); }

        /// ������������ǰʱ��
        double Elapsed() const 
        {
            auto now = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
            return (double)duration.count();
        }

        /// ���ع�񻯺������ʱ��
        std::string ElapsedString(bool precise = false) const 
        {
            return timeString(Elapsed(), precise);
        }

        /// ������������ǰʱ�䲢�����ü�����
        double Lap() 
        {
            auto now = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
            start = now;
            return (double)duration.count();
        }

        /// ���ع�񻯵���������ǰʱ�䲢�����ü�����
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