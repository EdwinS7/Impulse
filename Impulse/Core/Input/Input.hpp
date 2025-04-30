#ifndef INPUT_H
#define INPUT_H

#include "../Common.hpp"
#include "../Graphics/Types.hpp"

enum PointerStyle {
    Arrow = 32512,
    IBeam = 32513,
    Wait = 32514,
    Cross = 32515,
    UpArrow = 32516,

    Size = 32640,
    Icon = 32641,
    SizeNWSE = 32642,
    SizeNESW = 32643,
    SizeWE = 32644,
    SizeNS = 32645,
    SizeAll = 32646,

    No = 32648,
    Hand = 32649,
    AppStarting = 32650,
    Help = 32651,

    Pin = 32671,
    Person = 32672
};

class CInput {
public:
    void PoolInput( );

    bool IsActive( );

    bool IsKeyPressed( int key );
    bool IsKeyHeld ( int key );

    void SetCursorPosition( Vector2 position, bool actual_cursor );
    Vector2 GetCursorPosition( );

    PointerStyle GetCursorStyle( );
    void SetCursorStyle( PointerStyle pointer_style );

private:
    bool m_Active = false;
    bool m_AnyKeyPressed = false;

    uint8_t m_PreviousKeyStates[ 255 ];
    uint8_t m_KeyStates[ 255 ];

    PointerStyle m_CursorStyle{ PointerStyle::Arrow };
    Vector2 m_CursorPosition;

} extern Input;

#endif