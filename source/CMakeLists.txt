set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library PARENT_SCOPE)
set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library)
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include")
set(HEADER_RESOURCE "${PROJECT_SOURCE_DIR}/resourcesHID")

file(
    GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${HEADER_DIR}/*.hpp"
    "${HEADER_RESOURCE}/*.h"
)

add_library(${PROJECT_SOURCES_LIBRARY} STATIC
    Engine/Core.cpp
    Engine/Exceptions/Exception.cpp
    Engine/Exceptions/ParsingException.cpp
    Engine/StringUtils.cpp
    Engine/Resources/Loaders/Meshes/ObjMeshLoader.cpp
    Engine/Resources/Loaders/Shaders/SpirvShaderLoader.cpp
    Engine/Resources/Loaders/Texts/TextTxtLoader.cpp
    Engine/Resources/Loaders/Textures/GenericTextureLoader.cpp
    Engine/Resources/MeshResource.cpp
    Engine/Resources/Resource.cpp
    Engine/Resources/ResourceManager.cpp
    Engine/Resources/ShaderResource.cpp
    Engine/Resources/TextureResource.cpp
    Engine/Window.cpp
    ${HEADER_LIST}
 )

find_package(Vulkan REQUIRED)
find_package(portaudio REQUIRED)
find_path(STB_INCLUDE_DIRS "stb_image.h")

target_include_directories(
    ${PROJECT_SOURCES_LIBRARY} PUBLIC ${HEADER_DIR} PRIVATE ${STB_INCLUDE_DIRS}
)
target_link_libraries(
    ${PROJECT_SOURCES_LIBRARY} PRIVATE Vulkan::Vulkan portaudio
)

enable_warnings(${PROJECT_SOURCES_LIBRARY})
