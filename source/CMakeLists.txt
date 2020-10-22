set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library PARENT_SCOPE)
set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library)
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include")

file(
    GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${HEADER_DIR}/*.hpp"
)

add_library(${PROJECT_SOURCES_LIBRARY} STATIC
    Engine/Core.cpp
    Engine/Exception/Exception.cpp
    Engine/Exception/ParsingException.cpp
    Engine/StringUtils.cpp
    Engine/Resource/MeshLoader.cpp
    Engine/Resource/MeshResource.cpp
    Engine/Resource/Resource.cpp
    Engine/Resource/ResourceManager.cpp
    Engine/Resource/TextLoader.cpp
    Engine/Resource/TextureLoader.cpp
    ${HEADER_LIST}
)

find_package(Vulkan REQUIRED)
find_package(portaudio REQUIRED)

target_include_directories(
    ${PROJECT_SOURCES_LIBRARY} PUBLIC ${HEADER_DIR}
)
target_link_libraries(
    ${PROJECT_SOURCES_LIBRARY} PRIVATE Vulkan::Vulkan portaudio
)

enable_warnings(${PROJECT_SOURCES_LIBRARY})
