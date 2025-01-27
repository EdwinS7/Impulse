#include "Common.hpp"
#include "Core/FileSystem/FileSystem.hpp"
#include "Core/LuaU/Enviornment.hpp"

int main() {
    try {
        Enviornment Env;

        const std::string Script = FileSystem::ReadFile("Main.lua");

        if (!Env.LoadScript(Script)) {
            std::cerr << "Failed to load the script." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}