#pragma once

namespace tk
{
    class Timer {
    public:

        Timer();

        void start();
        void stop();
        double elapsed() const;
        bool running() const;
        bool isHighPerformance() const;

    private:
        double m_frequency;
        __int64 m_startTime;
        bool m_isHighPerformance;
        bool m_running;
    };

} // namespace aie

