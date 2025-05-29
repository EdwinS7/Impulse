// Standard Library
#include <cassert>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <variant>
#include <vector>
#include <format>

// Windows/System
#include <Windows.h>
#include <direct.h>
#include <filesystem>
#include <wininet.h>
#include <wincodec.h>

// Graphics (DirectX)
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>

#pragma comment(lib, "windowscodecs.lib")

// External Libraries
#include <nlohmann/json.hpp>
#include <cppcodec/base64_rfc4648.hpp>

#define CURL_STATICLIB
#include "Curl/Include/curl/curl.h"

// FreeType
#include "Freetype/freetype.h"
#include "Freetype/ft2build.h"

// Luau VM and Compiler
#include "LuaU/VM/Include/lualib.h"
#include "LuaU/VM/Src/ldo.h"
#include "Luau/VM/Src/lfunc.h"
#include "LuaU/Compiler/Include/Luau/BytecodeBuilder.h"
#include "LuaU/Compiler/Include/Luau/Compiler.h"
#include "LuaU/Compiler/Include/luacode.h"