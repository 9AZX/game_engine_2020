set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library PARENT_SCOPE)
set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library)
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include")

file(
    GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS
    "${HEADER_DIR}/*.hpp"
)

# TODO CHANGE THIS TO SHARED
add_library(${PROJECT_SOURCES_LIBRARY} STATIC
    Engine/Core.cpp
    Engine/Exceptions/Exception.cpp
    Engine/Exceptions/FileException.cpp
    Engine/Exceptions/GraphicsException.cpp
    Engine/Exceptions/ParsingException.cpp
    Engine/Graphics.cpp
    Engine/Graphics/DebugMessenger.cpp
    Engine/Graphics/Device.cpp
    Engine/Graphics/Instance.cpp
    Engine/Graphics/Mesh.cpp
    Engine/Graphics/Swapchain.cpp
    Engine/Graphics/ObjectRenderer.cpp
    Engine/Graphics/ObjectBuffers.cpp
    Engine/Graphics/CommandBuffer.cpp
    Engine/Graphics/VkTools.cpp
    Engine/Graphics/Camera.cpp
    Engine/Graphics/Vertex.cpp
    Engine/Graphics/Renderpass.cpp
    Engine/Graphics/RenderTarget.cpp
    Engine/Physics/ElementPhysics.cpp
    Engine/Physics/Bulletlink.cpp
    Engine/HID.cpp
    Engine/Graphics/GraphicsPipeline.cpp
    Engine/Logging/ConsoleSink.cpp
    Engine/Logging/FileSink.cpp
    Engine/Logging/Logger.cpp
    Engine/Logging/Sink.cpp
    Engine/Maths/Constants.cpp
    Engine/Maths/Matrix.cpp
    Engine/Maths/Matrix4.cpp
    Engine/Maths/Matrix4x3.cpp
    Engine/Maths/Quaternions.cpp
    Engine/Maths/Vector2.cpp
    Engine/Maths/Vector3.cpp
    Engine/Maths/vector4.cpp
    Engine/Resources/Loaders/Meshes/ObjMeshLoader.cpp
    Engine/Resources/Loaders/Shaders/SpirvShaderLoader.cpp
    Engine/Resources/Loaders/Texts/TextTxtLoader.cpp
    Engine/Resources/Loaders/Textures/GenericTextureLoader.cpp
    Engine/Resources/Resource.cpp
    Engine/Resources/ResourceManager.cpp
    Engine/Resources/ShaderResource.cpp
    Engine/Resources/TextureResource.cpp
    Engine/StringUtils.cpp
    Engine/Window.cpp
    ${HEADER_LIST}
    ${HEADER_DIR}/Engine/ResourcesHID/ResourceAcceleratorTable.rc
)

find_package(fmt CONFIG REQUIRED)
find_package(portaudio CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)


find_package(Vulkan REQUIRED)

find_path(STB_INCLUDE_DIRS "stb_image.h")

target_link_libraries(
    ${PROJECT_SOURCES_LIBRARY} PUBLIC fmt::fmt fmt::fmt-header-only portaudio Vulkan::Vulkan LinearMath Bullet3Common BulletDynamics BulletSoftBody
)

target_include_directories(
    ${PROJECT_SOURCES_LIBRARY} PUBLIC ${HEADER_DIR} PRIVATE ${STB_INCLUDE_DIRS}
)

enable_warnings(${PROJECT_SOURCES_LIBRARY})
