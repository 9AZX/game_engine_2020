set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library PARENT_SCOPE)
set(PROJECT_SOURCES_LIBRARY ${PROJECT_NAME}_library)
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include")
set(HEADER_DIR_GRAPHICS "${PROJECT_SOURCE_DIR}/include/graphics")

file(
    GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${HEADER_DIR}/*.hpp"
    "${HEADER_DIR_GRAPHICS}/*.hpp"
)

add_library(${PROJECT_SOURCES_LIBRARY} STATIC
    Core.cpp
    EngineWindow.cpp
    Graphics.cpp
    graphics/Instance.cpp
    graphics/Device.cpp
    ${HEADER_LIST}
)

find_package(Vulkan REQUIRED)
find_package(portaudio REQUIRED)

target_include_directories(
    ${PROJECT_SOURCES_LIBRARY} PUBLIC ${HEADER_DIR}
)
target_include_directories(
    ${PROJECT_SOURCES_LIBRARY} PUBLIC ${HEADER_DIR_GRAPHICS}
)
target_link_libraries(
    ${PROJECT_SOURCES_LIBRARY} PRIVATE Vulkan::Vulkan portaudio
)

enable_warnings(${PROJECT_SOURCES_LIBRARY})
