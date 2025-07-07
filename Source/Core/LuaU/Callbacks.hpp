#ifndef LUAU_CALLBACKS_H
#define LUAU_CALLBACKS_H

#include "../Common.hpp"
#include "../Graphics/Types.hpp"

using Arg = std::variant<
    int, float, double,
    bool,
    const char*, std::string,

    Vector2, Vector3, Color,
    Vertex, DrawCommand
>;

using Args = std::vector<Arg>;

using CallbackPair = std::pair<int, int>;
using CallbackPairList = std::vector<CallbackPair>;

class CCallbacks {
private:
    int m_ConnectionCount{ 0 };

    std::unordered_map<std::string, CallbackPairList> m_Connections = {
        {"present",             CallbackPairList{}},
        {"cursor_move",         CallbackPairList{}},
        {"key_pressed",         CallbackPairList{}},
        {"key_held",            CallbackPairList{}},
        {"shutdown",            CallbackPairList{}},
        {"fps_counter_update",  CallbackPairList{}}
    };
public:
    void RunConnection( const char* connection_name, const Args& args );
    int AddConnection( const char* connection_name, int function_reference );
    void RemoveConnection( int connection_id );
} extern Callbacks;

#endif