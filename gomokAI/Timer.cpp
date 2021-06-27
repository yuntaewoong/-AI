#include "Timer.h"

#include <SDL.h>
void Timer::Start()
{
    m_Started = true;
    m_Paused = false;

    m_StartTime = SDL_GetTicks();
    m_PausedTime = 0;
}
void Timer::Stop()
{
    m_Started = false;
    m_Paused = false;

    m_StartTime = 0;
    m_PausedTime = 0;
}
void Timer::Pause()
{
    if (m_Started && !m_Paused)
    {
        m_Paused = true;

        m_PausedTime = SDL_GetTicks() - m_StartTime;
        m_StartTime = 0;
    }
}
void Timer::Unpause()
{
    if (m_Started && m_Paused)
    {
        m_Paused = false;

        m_StartTime = SDL_GetTicks() - m_PausedTime;
        m_PausedTime = 0;
    }
}
int Timer::GetTicks()
{
    if (m_Started)
        return m_Paused ? m_PausedTime : SDL_GetTicks() - m_StartTime;
    return 0;
}