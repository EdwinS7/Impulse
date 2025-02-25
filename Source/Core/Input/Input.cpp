#include "Input.hpp"
#include "../LuaU/Environment.hpp"

void CInput::PoolInput( ) {
	m_Active = true; // Make this chekc if were focused
	m_AnyKeyPressed = false;

	uint8_t Buffer[ 256 ];

	if ( GetKeyboardState( Buffer ) ) {
		for ( int i = 0; i < 255; i++ ) {
			bool IsPressed = ( Buffer[ i ] & 0x80 ) != 0;
			bool WasPressed = m_KeyStates[ i ] & 0x01;

			m_KeyStates[ i ] = ( ( IsPressed ) ? 0x01 : 0x00 ) | ( WasPressed ? 0x02 : 0x00 );

			if ( IsPressed ) {
				m_AnyKeyPressed = true;
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
	return m_KeyStates[ key ] & 0x01;
}

void CInput::SetCursorPosition( Vector2 position, bool actual_cursor ) {
	if ( actual_cursor )
		SetCursorPos( position.x, position.y );
	else {
		m_CursorPosition = position;

		Environment.RunConnection( "cursor_move", { position } );
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