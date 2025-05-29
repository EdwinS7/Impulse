#include "Input.hpp"

#include "../LuaU/Environment.hpp"
#include "../Win32/Win32.hpp"

void CInput::PoolInput( ) {
	m_Active = ( GetForegroundWindow( ) == GetActiveWindow( ) );
	m_AnyKeyPressed = false;

	uint8_t Buffer[ 256 ] = { 0 };
	if ( GetKeyboardState( Buffer ) ) {
		for ( int i = 0; i < 256; i++ ) {
			const bool IsPressed = ( Buffer[ i ] & 0x80 ) != 0;
			const bool WasPressed = m_KeyStates[ i ] & 0x01;
			m_KeyStates[ i ] = ( ( IsPressed ) ? 0x01 : 0x00 ) | ( WasPressed ? 0x02 : 0x00 );

			if ( m_Active ) {
				if ( IsPressed && !WasPressed )
					Callbacks.RunConnection( "key_pressed", { i } );

				if ( IsPressed ) {
					Callbacks.RunConnection( "key_held", { i } );
					m_AnyKeyPressed = true;
				}
			}
		}
	}
}

bool CInput::IsActive( ) {
	return m_Active;
}

bool CInput::IsKeyPressed( int key ) {
	return ( m_KeyStates[ key ] & 0x01 ) && !( m_KeyStates[ key ] & 0x02 );
}

bool CInput::IsKeyHeld( int key ) {
	return ( m_KeyStates[ key ] & 0x01 ) != 0;
}

void CInput::SetCursorPosition( Vector2 position, bool actual_cursor ) {
	if ( actual_cursor )
		SetCursorPos( position.x, position.y );
	else {
		m_CursorPosition = position;
	}
}

Vector2 CInput::GetCursorPosition( ) {
	return m_CursorPosition;
}

PointerStyle CInput::GetCursorStyle( ) {
	return m_CursorStyle;
}

void CInput::SetCursorStyle( PointerStyle pointer_style ) {
	m_CursorStyle = pointer_style;
}

CInput Input;