#include "Engine/Core.hpp"

int main(void)
{
    Engine::Core core("Super jeu");

    core.init();
    core.getResourceManager()->registerResource(
        {
            Engine::ResourceType::MeshType,
            "skel",
            "resources/models/viking_room.obj"
        }
    );
    core.getResourceManager()->loadResources();

    while (1)
    {

        core.update();
    }
}
