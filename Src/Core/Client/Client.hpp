#ifndef CLIENT_H
#define CLIENT_H

#include "../Common.hpp"

class CClient {
    float m_WhenToUpdate{ 0.f };
    int m_FrameCount{ 0 };

    std::chrono::steady_clock::time_point m_TimePoint, m_FrameTime;
public:
    const char* Username = "admin";
    
    double DeltaTime{ 0.f }, RealTime{ 0.f };
    int Fps{ 60 };

    void Update( );
} extern Client;

#endif