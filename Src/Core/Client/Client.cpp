#include "Client.hpp"

#include "../LuaU/Callbacks.hpp"

void CClient::Update( ) {
    m_TimePoint = std::chrono::high_resolution_clock::now( );

    RealTime = static_cast< float >( std::chrono::duration_cast< std::chrono::duration<double> >( 
        m_TimePoint.time_since_epoch( ) ).count( ) 
    );
   
    DeltaTime = static_cast< float >( std::chrono::duration_cast< std::chrono::duration<double> >( 
        m_TimePoint - m_FrameTime ).count( )
    );

    m_FrameTime = m_TimePoint;

    if ( RealTime > m_WhenToUpdate ) {
        m_WhenToUpdate = RealTime + 1.f;
        Fps = m_FrameCount;

        Callbacks.RunConnection( "fps_counter_update", { 
            m_FrameCount
        } );

        m_FrameCount = 0;
    }
    else
        m_FrameCount++;
}

CClient Client;