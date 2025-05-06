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
#include <wincodec.h>

#pragma comment(lib, "windowscodecs.lib")

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#include <nlohmann/json.hpp>
#include <cppcodec/base64_rfc4648.hpp>

#include "LuaU/VM/Include/lualib.h"
#include "LuaU/Compiler/Include/Luau/BytecodeBuilder.h"
#include "LuaU/Compiler/Include/Luau/Compiler.h"
#include "LuaU/Compiler/Include/luacode.h"
#include "LuaU/VM/Src/ldo.h"
#include "Luau/VM/Src/lfunc.h"

#define CURL_STATICLIB
#include "Curl/Include/curl/curl.h"

#include "Freetype/ft2build.h"

#define SAFE_RELEASE(p) if (p) { \
    p->Release(); \
    p = nullptr; \
}