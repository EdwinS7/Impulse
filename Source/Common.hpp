#include "Windows.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <cassert>
#include <random>
#include <conio.h>
#include <iomanip>
#include <wininet.h>
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <direct.h>
#include <filesystem>
#include <variant>

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>


#include "LuaU/VM/Include/lualib.h"
#include "LuaU/Compiler/Include/Luau/BytecodeBuilder.h"
#include "LuaU/Compiler/Include/Luau/Compiler.h"
#include "LuaU/Compiler/Include/luacode.h"
#include "LuaU/VM/Src/ldo.h"
#include "Luau/VM/Src/lfunc.h"

#define CURL_STATICLIB
#include "Curl/Include/curl/curl.h"