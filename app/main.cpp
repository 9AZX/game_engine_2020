#include "Engine/Core.hpp"
#include "Engine/Logging/Logger.hpp"
#include "Engine/Logging/ConsoleSink.hpp"
#include "Engine/Logging/FileSink.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include <map>

int main(void)
{
    Engine::Core core("Super jeu");

    core.init();
    core.init();
    core.getResourceManager()->registerResource(
        {
            Engine::ResourceType::MeshType,
            "skel",
            "resources/skel.obj"
        }
    );
    core.getResourceManager()->loadResources();
    core.run();
}
