#include "Engine/Core.hpp"

int main(void)
{
    Engine::Core engine;

    engine.init();
    engine.getResourceManager()->registerResource(
        {
            Engine::ResourceType::MeshType,
            "skel",
            "resources/skel.obj"
        }
    );
    engine.getResourceManager()->loadResources();
    engine.run();
}
