#include "Common.hpp"
#include "Core/FileSystem/FileSystem.hpp"
#include "Core/LuaU/Enviornment.hpp"
#include "Core/Win32/Win32.hpp"

int main() {
    try {
        Enviornment Env;

        const std::string Script = FileSystem::ReadFile("Main.lua");

        if (!Env.LoadScript(Script)) {
            std::cerr << "Failed to load the script." << std::endl;
        }

        while ( Win32::DispatchMessages( ) ) {
            // NOTE: This runs until we close our window.
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}