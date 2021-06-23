#pragma once
class Timer
{
private:
    int m_StartTime;
    int m_PausedTime;
    bool m_Started;
    bool m_Paused;

public:
    Timer()
        : m_StartTime(0), m_PausedTime(0), m_Started(false), m_Paused(false) {}

    void Start();
    void Stop();
    void Pause();
    void Unpause();
    int GetTicks();

    inline bool IsStarted() const { return m_Started; }
    inline bool IsPaused() const { return m_Paused; }
};