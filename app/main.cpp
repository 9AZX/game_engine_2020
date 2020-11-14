#include "Engine/Core.hpp"

#include <iostream>
#include <map>

int main(void)
{
    Engine::Core core("Super jeu");

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
