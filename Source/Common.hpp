#include "Windows.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <cassert>
#include <random>
#include <lobject.h>
#include <conio.h>

#include "LuaU/VM/Include/lualib.h"
#include "LuaU/Compiler/Include/Luau/BytecodeBuilder.h"
#include "LuaU/Compiler/Include/Luau/Compiler.h"
#include "LuaU/Compiler/Include/luacode.h"

#define CURL_STATICLIB
#include "Curl/Include/curl/curl.h"